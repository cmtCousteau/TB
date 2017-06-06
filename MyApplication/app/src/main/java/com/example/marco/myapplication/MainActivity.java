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

    private boolean WRITE_OK = false;

    private int mStatus;

    private Handler mHandler;

    public static final int REQUEST_BT_PERMISSIONS = 0;
    public static final int REQUEST_BT_ENABLE = 1;

    public ArrayList<BluetoothGattCharacteristic> charas;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
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
            super.onCharacteristicWrite(gatt, characteristic, status);
            WRITE_OK = true;
            //Log.i(TAG, "Write callback : " + status);
        }

        @Override
        public void onCharacteristicRead(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            super.onCharacteristicRead(gatt, characteristic, status);
           // Log.i(TAG, "Read status : " + status);
        }

        @Override
        public void onCharacteristicChanged (BluetoothGatt gatt, BluetoothGattCharacteristic characteristic){
          //  Log.i(TAG, "Read status : " + characteristic.getValue());
        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                Log.i(TAG, "Service : " + mBluetoothGatt.getServices().toString());

                List<BluetoothGattService> services = mBluetoothGatt.getServices();
                List<BluetoothGattCharacteristic> gattCharacteristics;

                charas = new ArrayList<>();

                for (BluetoothGattService gattService : services) {
                    gattCharacteristics = gattService.getCharacteristics();
                    for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) {
                        charas.add(gattCharacteristic);

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
                    }
                }

                @Override
                public void onScanFailed(int errorCode) {
                    super.onScanFailed(errorCode);
                }


            };


    private void sendData(String data){

        int i = 0;

        // Défini le type de données (byte ou ASCII).
        rxBinary.setValue(new byte[]{0x01});
        while(mBluetoothGatt.writeCharacteristic(rxBinary)!= true){
            try {Thread.sleep(1);}
            catch(Exception e){}
        }

        // Envoi des données.
        rxData.setValue(data);
        while(mBluetoothGatt.writeCharacteristic(rxData) != true);{
            try {Thread.sleep(1);}
            catch(Exception e){}
        }


        /*rxBinary.setValue(new byte[]{0x01});
        mBluetoothGatt.writeCharacteristic(rxBinary);
        while(!WRITE_OK);




        rxData.setValue(data);
        mBluetoothGatt.writeCharacteristic(rxData);
        while(!WRITE_OK);

        WRITE_OK = false;*/




    }

    private void writeTest(){
        rxBinary.setValue(new byte[]{0x01});
        mBluetoothGatt.writeCharacteristic(rxBinary);
        try {Thread.sleep(200);}
        catch(Exception e){}

        rxData.setValue("test");
        mBluetoothGatt.writeCharacteristic(rxData);
        try {Thread.sleep(200);}
        catch(Exception e){}
    }

    private String readData(){

        String valueToReturn = "";

        

        while(mBluetoothGatt.readCharacteristic(txData) != true);

        while(txData.getValue() == null);

        return new String(txData.getValue());
    }

    private void readTest(){
        resultTextView.setText("read en cours");
        mBluetoothGatt.readCharacteristic(txData);
        try {Thread.sleep(200);}
        catch(Exception e){}

        if(txData.getValue() != null) {
            Log.i(TAG, "Chara value   : " + new String(txData.getValue()));
            resultTextView.setText("Chara value   : " + new String(txData.getValue()));
            // On prévient qu'on a bien pu lire.
            txRead.setValue(new byte[]{0x01});
            mBluetoothGatt.writeCharacteristic(txRead);
        }
    }

    // ---------------------------------------------------------------------------------------------
    // Listener
    private OnClickListener startScanListener = new OnClickListener() {

        @Override
        public void onClick(View v) {
            resultTextView.setText("start");
            mBluetoothLeScanner.startScan(mLeScanCallback);
            btnStopScan.setEnabled(true);
            btnRead.setEnabled(true);
            btnDisconnect.setEnabled(true);
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
            resultTextView.setText(readData());
            //readTest();
        }
    };

    private OnClickListener btnWriteListener = new OnClickListener() {
        @Override
        public void onClick(View v) {
            resultTextView.setText("write");
           // writeTest();
            mBluetoothGatt.requestConnectionPriority(BluetoothGatt.CONNECTION_PRIORITY_HIGH);



            Log.i(TAG, "Appel fonction d'envoi.");

            new Thread(new Runnable() {
                public void run() {
                    for(int i = 0; i <= 210; i++){
                        Integer tmpInt = i;
                        sendData("" + tmpInt.toString());
                    }
                }
            }).start();


/*
            for(int i = 0; i < 2; i++){
                Integer tmpInt = i;
                sendData("test" + tmpInt.toString());
                while(true){
                    if(readData().equalsIgnoreCase("ok" + tmpInt.toString()))
                        break;
                }

            }*/
        }
    };

    private OnClickListener btnDisconnectListener = new OnClickListener() {
        @Override
        public void onClick(View v) {
            resultTextView.setText("disconnected");
            Log.i(TAG, "BLEd device disconnected.");
            mBluetoothGatt.close();
            mBluetoothGatt.disconnect();

        }
    };
}




