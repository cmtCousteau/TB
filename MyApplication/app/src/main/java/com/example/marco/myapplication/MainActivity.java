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
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
                Log.i(TAG, "Service : " + gatt.getServices().toString());

                List<BluetoothGattService> services = gatt.getServices();
                List<BluetoothGattCharacteristic> gattCharacteristics;
                //ArrayList<BluetoothGattCharacteristic> charas;
                charas = new ArrayList<>();
                for (BluetoothGattService gattService : services) {
                   // Log.i(TAG, "---------------------------------------------------------- : ");
                   // Log.i(TAG, "Service : " + gattService);
                    gattCharacteristics = gattService.getCharacteristics();
                    for (BluetoothGattCharacteristic gattCharacteristic : gattCharacteristics) {
                       // gatt.readCharacteristic(gattCharacteristic);
                        charas.add(gattCharacteristic);
                      //  Log.i(TAG, "Chara uuid    : " + gattCharacteristic.getUuid());
                       // Log.i(TAG, "read attempt  : " + gatt.readCharacteristic(gattCharacteristic));
                   //   Log.i(TAG, "Write attempt : " + gatt.writeCharacteristic(gattCharacteristic));
                      //  Log.i(TAG, "permission    : " + gattCharacteristic.getPermissions());

                        // recpère le nom
                       /* if(gattCharacteristic.getUuid().toString().equalsIgnoreCase("3347ab01-fb94-11e2-a8e4-f23c91aec05e")) {

                            gatt.get
                            Log.i(TAG, "lecture : " + gatt.readCharacteristic(gattCharacteristic));

                        }
                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase("3347aad2-fb94-11e2-a8e4-f23c91aec05e")) {
                            Log.i(TAG, "test");
                            Log.i(TAG, "ca" + gatt.readCharacteristic(gattCharacteristic));
                        }
                        if(gattCharacteristic.getUuid().toString().equalsIgnoreCase("3347AAB2-FB94-11E2-A8E4-F23C91AEC05E")) {
                            Log.i(TAG, "Write attempt : " + gatt.writeCharacteristic(gattCharacteristic));
                        }*/
                    }
                }
            }
        }

       /* @Override
        public void onCharacteristicRead(BluetoothGatt gatt,BluetoothGattCharacteristic characteristic, int status) {
            if (status == BluetoothGatt.GATT_SUCCESS) {
               // Log.i(TAG, "Read chara : ----------------------------");
                Log.i(TAG, characteristic.getStringValue(0));
                //Log.i(TAG, "Read chara : ----------------------------");
            }
        }*/

       /* @Override
        public void onCharacteristicChanged(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic) {
        }*/

      /*  @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status) {
            Log.i(TAG, "cacacacacaca : ");
            super.onCharacteristicWrite(gatt, characteristic, status);
            boolean stat = characteristic.setValue("0");
            Log.i(TAG, "Write result : " + stat);
        }*/
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

    private void readTest(){
        resultTextView.setText("read en cours");

        BluetoothGattCharacteristic ch;
        for (BluetoothGattCharacteristic gattCharacteristic : charas) {
            if( gattCharacteristic.getUuid().toString().equals("3347ab01-fb94-11e2-a8e4-f23c91aec05e")) {
                ch =  gattCharacteristic;
                mBluetoothGatt.readCharacteristic(gattCharacteristic);
                Log.i(TAG, "Chara uuid    : " + ch.getUuid());

                if(ch.getValue() != null) {
                    Log.i(TAG, "Chara value   : " + new String(ch.getValue()));
                }

                byte uncompressed[] = ("sdadsa").getBytes();
                ch.setValue(uncompressed);
                mBluetoothGatt.writeCharacteristic(ch);

               /* for (BluetoothGattDescriptor descriptor:gattCharacteristic.getDescriptors()){
                    //mBluetoothGatt.readDescriptor(descriptor);
                    Log.e(TAG, "BluetoothGattDescriptor : " + descriptor.getUuid().toString() + " Value : " + descriptor.getValue());
                }*/

                //
            }
        }
    }

    private OnClickListener startScanListener = new OnClickListener() {

        @Override
        public void onClick(View v) {
            resultTextView.setText("start");
            mBluetoothLeScanner.startScan(mLeScanCallback);
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
            resultTextView.setText("read");
            readTest();
        }
    };

    private OnClickListener btnDisconnectListener = new OnClickListener() {
        @Override
        public void onClick(View v) {
            resultTextView.setText("disconnected");
            Log.i(TAG, "BLEd device disconnected.");
            //mBluetoothGatt.close();
            mBluetoothGatt.disconnect();
        }
    };
}




