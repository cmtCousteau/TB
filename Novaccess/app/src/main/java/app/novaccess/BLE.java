package app.novaccess;

import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;

import java.util.List;
import java.util.UUID;


/**
 * Created by marco on 22.06.2017.
 */

public class BLE {

    private int mStatus;
    private BluetoothGatt mBluetoothGatt = null;
    private Context context;
    private int RSSI = 0;

    private List<BluetoothDevice>deviceList;

    Boolean READ_CHARACTERISTIC_OK = false;
    Boolean READ_DESCRIPTOR_OK = false;
    Boolean READ_RSSI_OK = false;

    public BLE(Context context){
        this.context = context;
    }

    public boolean connection(BluetoothDevice device){
        mBluetoothGatt = device.connectGatt(context, false, mGattCallback);
        mBluetoothGatt.readRemoteRssi();
        return true;
       //1 return mBluetoothGatt.getConnectionState(device) == BluetoothProfile.STATE_CONNECTED;
    }

    public void disconnect(){
        mBluetoothGatt.disconnect();
    }

    private ScanCallback mLeScanCallback =
            new ScanCallback() {

                @Override
                public void onScanResult(int callbackType, final ScanResult result) {

                    deviceList.add(result.getDevice());
                }

                @Override
                public void onScanFailed(int errorCode) {
                    super.onScanFailed(errorCode);
                }
            };

    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {

        @Override
        public void onDescriptorRead(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status){
            READ_DESCRIPTOR_OK = true;
        }

        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {

            if (newState == BluetoothProfile.STATE_CONNECTED) {

                mBluetoothGatt.readRemoteRssi();
                gatt.discoverServices();
            }
            else if (newState == BluetoothProfile.STATE_DISCONNECTED) {

            }
        }
        @Override
        public void onReadRemoteRssi (BluetoothGatt gatt,int rssi,int status){
            RSSI = rssi;
        }

        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {

        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            READ_CHARACTERISTIC_OK = true;
        }

        @Override
        public void onCharacteristicChanged (BluetoothGatt gatt, BluetoothGattCharacteristic characteristic){

        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {

        }
    };

    public List<BluetoothDevice> getDeviceList(){
        return deviceList;
    }

    public List<BluetoothGattService> getServicesList(){
        return mBluetoothGatt.getServices();
    }

    public BluetoothGattService getService (UUID serviceUuid){
        return mBluetoothGatt.getService(serviceUuid);
    }

    public List<BluetoothGattCharacteristic> getCharactersticsList(BluetoothGattService service){
        return service.getCharacteristics();
    }

    public BluetoothGattCharacteristic getCharacterstics(BluetoothGattService service, UUID characteristicUuid){
        return service.getCharacteristic(characteristicUuid);
    }

    public List<BluetoothGattDescriptor> getDescriptorList(BluetoothGattCharacteristic characteristic){
        return characteristic.getDescriptors();
    }

    public BluetoothGattDescriptor getDescriptor(BluetoothGattCharacteristic characteristic, UUID descriptorUuid){
        return characteristic.getDescriptor(descriptorUuid);
    }

    public void writeCharacteristicString(BluetoothGattCharacteristic characteristic, String data){

        characteristic.setValue(data);
        while(mBluetoothGatt.writeCharacteristic(characteristic) != true);{
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
    }

    public String readCharacteristicString(BluetoothGattCharacteristic characteristic){

        while(mBluetoothGatt.readCharacteristic(characteristic) != true){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }

        while(READ_CHARACTERISTIC_OK == false){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
        READ_CHARACTERISTIC_OK = false;

        return  new String(characteristic.getValue());
    }

    private String readDecriptorString(BluetoothGattDescriptor descriptor){

        while(mBluetoothGatt.readDescriptor(descriptor) != true){

        }

        while(READ_DESCRIPTOR_OK == false){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }
        READ_DESCRIPTOR_OK = false;

        return  new String(descriptor.getValue());
    }

    public int getRssi(){
        return RSSI*(-1);
    }

}
