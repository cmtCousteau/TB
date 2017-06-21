package com.example.marco.myapplication;

import android.Manifest;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothGattDescriptor;



import android.content.Intent;
import android.media.audiofx.AudioEffect;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.TextView;
import android.view.View;
import android.view.View.OnClickListener;
import android.os.Handler;
import android.content.Context;

import java.util.List;
import java.util.ArrayList;
import java.lang.Thread;
import java.nio.charset.*;
import java.util.UUID;



public class MainActivity extends AppCompatActivity {

    private BluetoothAdapter mBluetoothAdapter  = null;
    private BluetoothLeScanner mBluetoothLeScanner = null;

    private static final String TAG = "MainActivity";

    private BluetoothGatt mBluetoothGatt;

    private TextView resultTextView = null;
    private Button btnStartScan = null;
    private Button btnStopScan = null;
    private Button btnRead = null;
    private Button btnDisconnect = null;
    private Button btnWrite = null;


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

    private boolean READ_OK = false;

    private int mStatus;

    private Handler mHandler;


    public static final int REQUEST_BT_PERMISSIONS = 0;
    public static final int REQUEST_BT_ENABLE = 1;

    public ArrayList<BluetoothGattCharacteristic> charas;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setContentView(R.layout.activity_main);

        mHandler = new Handler();
        // Textview contenant les résultats
        resultTextView = (TextView)findViewById(R.id.txvResult);

        // Bouton de scan
        btnStartScan = (Button)findViewById(R.id.btnStartScan);
        btnStartScan.setOnClickListener(startScanListener);
        // Bouton pour arrêter le scan
        btnStopScan = (Button)findViewById(R.id.btnStopScan);
        btnStopScan.setOnClickListener(stopScanListener);
        // Bouton pour afficher les résultats
        btnRead = (Button)findViewById(R.id.btnRead);
        btnRead.setOnClickListener(btnReadListener);
        // Bouton de déconnection
        btnDisconnect = (Button)findViewById(R.id.btnDisconnect);
        btnDisconnect.setOnClickListener(btnDisconnectListener);
        // Bouton pour écrire
        btnWrite = (Button)findViewById(R.id.btnWrite);
        btnWrite.setOnClickListener(btnWriteListener);




        btnRead.setEnabled(false);
        btnDisconnect.setEnabled(false);
        btnStopScan.setEnabled(false);

        this.mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        this.resultTextView.setText(mBluetoothAdapter.toString());

        mBluetoothAdapter.getBluetoothLeScanner();
        this.mBluetoothLeScanner = mBluetoothAdapter.getBluetoothLeScanner();
    }

    @Override
    protected void onResume() {
        super.onResume();
        init();
    }

    public Context getContext() {
        return (Context)this;
    }


    private void init(){
        checkBtPermissions();
        enableBt();
    }

    public void enableBt(){
        if (mBluetoothAdapter == null) {
            // Device does not support Bluetooth
        }
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_BT_ENABLE);
        }
    }

    // ATTENTIUON VERSION 23 SEULEMENT
    public void checkBtPermissions() {
       // this.requestPermissions(
         //       new String[]{
           //             Manifest.permission.BLUETOOTH, Manifest.permission.BLUETOOTH_ADMIN, Manifest.permission.ACCESS_COARSE_LOCATION
         //       },
          //      REQUEST_BT_PERMISSIONS);
    }

    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {

        @Override
        public void onDescriptorRead(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status){
            READ_OK = true;
        }

        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {

            if (newState == BluetoothProfile.STATE_CONNECTED) {

                Log.i(TAG, "Connected to GATT server.");
                mStatus = newState;
                mBluetoothGatt.discoverServices();



                //gatt.discoverServices();

            } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                Log.i(TAG, "Disconnected from GATT server.");
                mStatus = newState;
            }
        }

        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            Log.i(TAG, "Write callback : " + status);
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
           // super.onCharacteristicRead(gatt, characteristic, status);
            Log.i(TAG, "Read status : " + status);
            READ_OK = true;
        }

        @Override
        public void onCharacteristicChanged (BluetoothGatt gatt, BluetoothGattCharacteristic characteristic){
            Log.i(TAG, "Read status : " + "CHANGED" + " new value : " + new String(characteristic.getValue()));
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
    };

    private ScanCallback mLeScanCallback =
            new ScanCallback() {

                @Override
                public void onScanResult(int callbackType, final ScanResult result) {

                   /* Button newButton = new Button(MainActivity.this);
                    newButton.setText(result.getDevice().getName());
                    newButton.setLayoutParams(new LayoutParams(LayoutParams.FILL_PARENT,LayoutParams.WRAP_CONTENT));
                    ViewGroup linearLayout = (ViewGroup) findViewById(R.id.linearLayoutID);
                    linearLayout.addView(newButton);*/

                    // Si le device trouvé est le sable-x
                    if(result.getDevice().getName() != null && result.getDevice().getName().contains("Sa")) {
                        resultTextView.setText("Name\t\t\t: " + result.getDevice().getName() + "\n MAC adress\t: " + result.getDevice().getAddress());
                        BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(result.getDevice().getAddress());
                        // Connection au gatt
                        mBluetoothGatt = device.connectGatt(MainActivity.this, false, mGattCallback);
                        mBluetoothLeScanner.stopScan(mLeScanCallback);

                        // Comme on est connecté on active les autres boutons.
                        btnRead.setEnabled(true);
                        btnRead.setBackground(getContext().getResources().getDrawable(R.drawable.button_red, null));

                        btnWrite.setEnabled(true);
                        btnWrite.setBackground(getContext().getResources().getDrawable(R.drawable.button_red, null));

                        btnDisconnect.setEnabled(true);
                        btnDisconnect.setBackground(getContext().getResources().getDrawable(R.drawable.button_red, null));
                    }
                }

                @Override
                public void onScanFailed(int errorCode) {
                    super.onScanFailed(errorCode);
                }
            };


    private void sendData(String data){

        // Envoi des données.
        rxData.setValue(data);
        while(mBluetoothGatt.writeCharacteristic(rxData) != true);{
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
    }

    private String readRxRead(){
        while(mBluetoothGatt.readCharacteristic(rxRead) != true){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }

        while(READ_OK == false){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
        READ_OK = false;

        Byte var = rxRead.getValue()[0];
        Log.i(TAG, "Value : " +  var.toString());
        return var.toString();
    }


    private String readTxData(){
        if(mBluetoothGatt == null)
            return "Error";

        while(mBluetoothGatt.readCharacteristic(txData) != true){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }

        while(READ_OK == false){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
        READ_OK = false;

        String data = new String(txData.getValue());

        // Sorcellerie
       /* UUID uuid = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb");
        BluetoothGattDescriptor descriptor = txData.getDescriptor(uuid);
        descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
        mBluetoothGatt.writeDescriptor(descriptor);

        mBluetoothGatt.setCharacteristicNotification(txData,true);
        txData.setWriteType(BluetoothGattCharacteristic.WRITE_TYPE_DEFAULT);*/

        for(BluetoothGattDescriptor descriptor : txData.getDescriptors()){
            mBluetoothGatt.readDescriptor(descriptor);
            while(READ_OK == false){
                try {Thread.sleep(1);}
                catch(Exception e){}
            }
            READ_OK = false;

            Log.i(TAG, "Descriptor : " +  new String(descriptor.getValue()));
        }


        txRead.setValue(new byte[]{0x01});
        mBluetoothGatt.writeCharacteristic(txRead);

        Log.i(TAG, "Value : " +  data);

        return data;
    }

    private void setDataAscii(){
        // Défini le type de données (byte ou ASCII).
        rxBinary.setValue(new byte[]{0x01});
        while(mBluetoothGatt.writeCharacteristic(rxBinary)!= true){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
    }

    private void demo(){

        String tmp;

        sendData("Voltage");
        tmp = readTxData();
        resultTextView.setText("Voltage : " + tmp + "v");

        sendData("Courant");
        tmp = readTxData();
        resultTextView.setText(resultTextView.getText() + "\nCourant : " + tmp + "A");

        sendData("Cosphi");
        tmp = readTxData();
        resultTextView.setText(resultTextView.getText() + "\nCosphi : " + tmp);

        sendData("PuissanceInst");
        tmp = readTxData();
        resultTextView.setText(resultTextView.getText() + "\nPuissance instantanée : " + tmp + "Wh");

        sendData("Frequence");
        tmp = readTxData();
        resultTextView.setText(resultTextView.getText() + "\nFrequence : " + tmp + "Hz");

        sendData("PuissanceAgre");
        tmp = readTxData();
        resultTextView.setText(resultTextView.getText() + "\nPuissance agrégée : " + tmp + "kWh");

        sendData("Uptime");
        tmp = readTxData();
        resultTextView.setText(resultTextView.getText() + "\nUptime : " + tmp + "h");


    }

    // ---------------------------------------------------------------------------------------------
    // Listener
    private OnClickListener startScanListener = new OnClickListener() {

        @Override
        public void onClick(View v) {
            resultTextView.setText("start");
            mBluetoothLeScanner.startScan(mLeScanCallback);

            btnStopScan.setEnabled(true);
            btnStopScan.setBackground(getContext().getResources().getDrawable(R.drawable.button_red, null));
        }
    };

    private OnClickListener stopScanListener = new OnClickListener() {
        @Override
        public void onClick(View v) {
            resultTextView.setText("stop");
            mBluetoothLeScanner.stopScan(mLeScanCallback);
        }
    };

    private OnClickListener btnReadListener = new OnClickListener() {
        @Override
        public void onClick(View v) {

            /*if(mBluetoothGatt == null) {
                resultTextView.setText("Read error");
                return;
            }*/

            //setDataAscii();
            //demo();
            resultTextView.setText(readTxData());
        }
    };



    private OnClickListener btnWriteListener = new OnClickListener() {
        @Override
        public void onClick(View v) {

            if(mBluetoothGatt == null){
                resultTextView.setText("Write error");
                return;
            }

            mBluetoothGatt.requestConnectionPriority(BluetoothGatt.CONNECTION_PRIORITY_HIGH);

            Log.i(TAG, "Appel fonction d'envoi.");
            Thread tSend = new Thread(new Runnable() {
                public void run() {

                    setDataAscii();
                    for(int i = 0; i <= 9; i++){
                       // resultTextView.setText("Sending data " + i + "/" + "200");
                        Integer tmpInt = i;
                        sendData("abcdefghijkl" + tmpInt.toString());

                        /*while(!readTxData().equalsIgnoreCase(tmpInt.toString())){
                            try {Thread.sleep(1);}
                            catch(Exception e){}
                        }*/
                    }
                }
            });

            tSend.start();


           try {
                tSend.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            resultTextView.setText("Sending data terminated !");
        }
    };

    private OnClickListener btnDisconnectListener = new OnClickListener() {
        @Override
        public void onClick(View v) {
            resultTextView.setText("disconnected");
            Log.i(TAG, "BLEd device disconnected.");
            mBluetoothGatt.close();
            mBluetoothGatt.disconnect();

            btnRead.setEnabled(false);
            btnRead.setBackground(getContext().getResources().getDrawable(R.drawable.button_disable, null));

            btnWrite.setEnabled(false);
            btnWrite.setBackground(getContext().getResources().getDrawable(R.drawable.button_disable, null));

            btnStopScan.setEnabled(false);
            btnStopScan.setBackground(getContext().getResources().getDrawable(R.drawable.button_disable, null));

            btnDisconnect.setEnabled(false);
            btnDisconnect.setBackground(getContext().getResources().getDrawable(R.drawable.button_disable, null));

        }
    };
}




