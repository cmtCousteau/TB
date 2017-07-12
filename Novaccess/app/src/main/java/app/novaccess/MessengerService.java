package app.novaccess;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.bluetooth.le.ScanSettings;
import android.content.Context;
import android.content.Intent;
import android.media.audiofx.AudioEffect;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.util.Log;
import android.widget.Toast;

import java.util.UUID;

import java.util.List;
import java.util.UUID;
import java.util.List;

import static android.bluetooth.BluetoothAdapter.STATE_CONNECTED;
import static android.bluetooth.BluetoothAdapter.STATE_CONNECTING;
import static android.bluetooth.BluetoothGattCharacteristic.PERMISSION_READ;
import static android.bluetooth.BluetoothGattCharacteristic.PROPERTY_READ;
import static android.bluetooth.BluetoothProfile.STATE_DISCONNECTED;
import static android.content.ContentValues.TAG;
import static app.novaccess.BluetoothLeService.ACTION_GATT_CONNECTED;
import static app.novaccess.BluetoothLeService.ACTION_GATT_DISCONNECTED;

/**
 * Created by marco on 29.06.2017.
 */

public class MessengerService extends Service {
    /** Command to the service to display a message */
    static final int MSG_SAY_HELLO = 1;
    static final int START_BLE_SCAN = 2;
    static final int START_BLE_DISCOVERY = 3;
    static final int BLE_CONNECT = 4;
    static final int BLE_DISCONNECT = 5;
    static final int GET_CONNECTED_BLE_ADDRESS = 6;
    static final int READ_VALUE = 7;
    static final int WRITE_VALUE =8;

    static String CONNECTED_ADDRESS;


    private final String txDataUUID   = "3347AB01-FB94-11E2-A8E4-F23C91AEC05E"; // peripheral  => central
    private final String rxDataUUID   = "3347AB02-FB94-11E2-A8E4-F23C91AEC05E"; // central => peripheral
    private final String txReadUUID   = "3347AB03-FB94-11E2-A8E4-F23C91AEC05E"; // read by central
    private final String rxReadUUID   = "3347AB04-FB94-11E2-A8E4-F23C91AEC05E"; // peripheral  read
    private final String txBinaryUUID = "3347AB05-FB94-11E2-A8E4-F23C91AEC05E"; // Type of data (0 binay, 1 ascii)
    private final String rxBinaryUUID = "3347AB06-FB94-11E2-A8E4-F23C91AEC05E"; // Type of data (0 binay, 1 ascii)

    private BluetoothGattCharacteristic txData;
    private BluetoothGattCharacteristic rxData;
    private BluetoothGattCharacteristic txRead;
    private BluetoothGattCharacteristic rxRead;
    private BluetoothGattCharacteristic txBinary;
    private BluetoothGattCharacteristic rxBinary;


    private BluetoothManager mBluetoothManager;
    private BluetoothAdapter mBluetoothAdapter;
    private BluetoothLeScanner mBluetoothLeScanner;
    private BluetoothGatt mBluetoothGatt;
    private int mConnectionState = STATE_DISCONNECTED;

    BluetoothGattCharacteristic CHARA;



    /**
     * Handler of incoming messages from clients.
     */
    class IncomingHandler extends Handler {

        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case MSG_SAY_HELLO:
                    Toast.makeText(getApplicationContext(), "hello!", Toast.LENGTH_SHORT).show();
                    break;
                case START_BLE_SCAN:
                    break;
                case START_BLE_DISCOVERY:
                    initialize();
                    startDiscovery();
                    break;
                case BLE_CONNECT:
                    String address = ((Intent)msg.obj).getStringExtra("deviceAddress");
                    connect(address);
                    test();
                    while(mConnectionState != BluetoothAdapter.STATE_CONNECTED);
                    break;
                case BLE_DISCONNECT:
                    disconnect();
                    while(mConnectionState != BluetoothAdapter.STATE_DISCONNECTED);
                    close();
                    break;
                case GET_CONNECTED_BLE_ADDRESS:
                    Toast.makeText(getApplicationContext(), CONNECTED_ADDRESS, Toast.LENGTH_SHORT).show();
                    break;
                case READ_VALUE:
                   // String characteristic = ((Intent)msg.obj).getStringExtra("deviceAddress");
                    readCharacteristicString();
                    break;
                case WRITE_VALUE:
                    String data = ((Intent)msg.obj).getStringExtra("data");
                    writeCharacteristicString(data);
                    break;
                default:
                    super.handleMessage(msg);
            }
        }
    }

    /**
     * Target we publish for clients to send messages to IncomingHandler.
     */
    final Messenger mMessenger = new Messenger(new IncomingHandler());

    /**
     * When binding to the service, we return an interface to our messenger
     * for sending messages to the service.
     */
    @Override
    public IBinder onBind(Intent intent) {
        Toast.makeText(getApplicationContext(), "binding", Toast.LENGTH_SHORT).show();

        //android.os.Debug.waitForDebugger();
        return mMessenger.getBinder();
    }

    private void broadcastUpdate(Intent intent) {
        sendBroadcast(intent);
    }

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


    public void startDiscovery(){
        if(mBluetoothAdapter.isDiscovering())
            mBluetoothAdapter.cancelDiscovery();

        mBluetoothAdapter.startDiscovery();
    }

    public void cancelDiscovery(){
        mBluetoothAdapter.cancelDiscovery();
    }

    public boolean initialize() {
        // For API level 18 and above, get a reference to BluetoothAdapter through
        // BluetoothManager.
        if (mBluetoothManager == null) {
            mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
            if (mBluetoothManager == null) {
                Log.e(TAG, "Unable to initialize BluetoothManager.");
                return false;
            }
        }

        mBluetoothAdapter = mBluetoothManager.getAdapter();
        if (mBluetoothAdapter == null) {
            Log.e(TAG, "Unable to obtain a BluetoothAdapter.");
            return false;
        }
        return true;
    }


    public boolean connect(final String address) {

        cancelDiscovery();

        if (mBluetoothAdapter == null || address == null) {
            Log.w(TAG, "BluetoothAdapter not initialized or unspecified address.");

            return false;
        }

        final BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
        if (device == null) {
            Log.w(TAG, "Device not found.  Unable to connect.");
            return false;
        }

        mBluetoothGatt = device.connectGatt(this, false, mGattCallback);
        Log.d(TAG, "Trying to create a new connection.");
        mConnectionState = STATE_CONNECTING;
        return true;
    }

    public void disconnect() {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.disconnect();
    }

    public void close() {
        if (mBluetoothGatt == null) {
            return;
        }
        mBluetoothGatt.close();
        mBluetoothGatt = null;
    }

    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {

            if (newState == BluetoothProfile.STATE_CONNECTED) {


                gatt.discoverServices();
                CONNECTED_ADDRESS = gatt.getDevice().getAddress();

                mConnectionState = STATE_CONNECTED;
                mBluetoothGatt.readRemoteRssi();
                Log.i(TAG, "Connected to GATT server.");

            } else if (newState == STATE_DISCONNECTED) {
                mConnectionState = STATE_DISCONNECTED;
                Log.i(TAG, "Disconnected from GATT server.");
            }
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                Log.i(TAG, "Service : " + mBluetoothGatt.getServices().toString());

                List<BluetoothGattService> services = mBluetoothGatt.getServices();
                List<BluetoothGattCharacteristic> gattCharacteristics;

                for (BluetoothGattService gattService : services) {
                    gattCharacteristics = gattService.getCharacteristics();

                    for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) {

                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase(txDataUUID)){
                            txData = gattCharacteristic;
                        }

                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase(rxDataUUID)){
                            rxData = gattCharacteristic;
                        }

                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase(txReadUUID)){
                            txRead = gattCharacteristic;
                        }

                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase(rxReadUUID)){
                            rxRead = gattCharacteristic;
                        }

                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase(txBinaryUUID)){
                            txBinary = gattCharacteristic;
                        }

                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase(rxBinaryUUID)){
                            rxBinary = gattCharacteristic;
                        }
                    }
                }
            }
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {

            super.onCharacteristicRead(gatt,characteristic,status);
            //READ_CHARACTERISTIC_OK = true;

            Intent intent = new Intent();
            intent.setAction("CHARACTERISTIC_READ");
            intent.putExtra("value", new String(characteristic.getValue()));

            sendBroadcast(intent);
            sendBroadcast(intent);
            sendBroadcast(intent);
            sendBroadcast(intent);
        }
    };

    public void readCharacteristicString(){

        mBluetoothGatt.readCharacteristic(txData);


       /* while(READ_CHARACTERISTIC_OK == false){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
        READ_CHARACTERISTIC_OK = false;*/

        //return  new String(characteristic.getValue());
    }

    public void writeCharacteristicString(String data){

        //Défini le format des données (ASCII).
        rxBinary.setValue(new byte[]{0x01});
        while(mBluetoothGatt.writeCharacteristic(rxBinary)!= true){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }

    //    Toast.makeText(getApplicationContext(), "Write send", Toast.LENGTH_SHORT).show();
        rxData.setValue(data);
        while(mBluetoothGatt.writeCharacteristic(rxData)!= true){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
    }


    public void test() {

        UUID uuid1 = UUID.fromString("0000-0000-000-000-000");
        UUID uuid2 = UUID.fromString("0000-0000-000-000-001");

        CHARA = new BluetoothGattCharacteristic(uuid1, PROPERTY_READ, PERMISSION_READ);
        BluetoothGattDescriptor descr = new BluetoothGattDescriptor(uuid2, PERMISSION_READ);
        descr.setValue("Voltage".getBytes());
        CHARA.setValue("230".getBytes());
        CHARA.addDescriptor(descr);
    }

}
