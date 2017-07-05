package app.novaccess;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothManager;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class StartMenu extends AppCompatActivity {

    private List<String> listDeviceFound = new ArrayList<>();
    private List<Integer> listPower = new ArrayList<>();
    private List<String> listAddress = new ArrayList<>();

    private ListView listViewDevice;

    Messenger mService = null;
    boolean mBound;

    private ServiceConnection mConnection = new ServiceConnection() {
        public void onServiceConnected(ComponentName className, IBinder service) {
            // This is called when the connection with the service has been
            // established, giving us the object we can use to
            // interact with the service.  We are communicating with the
            // service using a Messenger, so here we get a client-side
            // representation of that from the raw IBinder object.
            mService = new Messenger(service);

            Message msg = Message.obtain(null, MessengerService.START_BLE_DISCOVERY, 0, 0);
            try {
                mService.send(msg);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

        public void onServiceDisconnected(ComponentName className) {
            // This is called when the connection with the service has been
            // unexpectedly disconnected -- that is, its process crashed.
            mService = null;
            mBound = false;
        }
    };

    public void enableBt(){
        BluetoothManager mBluetoothManager;
        BluetoothAdapter mBluetoothAdapter;

        mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
        mBluetoothAdapter = mBluetoothManager.getAdapter();

        if (mBluetoothAdapter == null) {
            // Device does not support Bluetooth
        }
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, 1);
        }
    }


    public Context getContext() {
        return (Context)this;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_start_menu);

        IntentFilter filter = new IntentFilter();
        filter.addAction(BluetoothDevice.ACTION_FOUND);
        filter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED);
        registerReceiver(mReceiver, filter);

        enableBt();

        listViewDevice = (ListView) findViewById(R.id.listDevice);

        android.widget.SearchView searchDevice = (android.widget.SearchView) findViewById(R.id.searchDevice);

        CustomListDevice adapter = new CustomListDevice(StartMenu.this,listDeviceFound,listPower, listAddress);
        listViewDevice.setAdapter(adapter);

        listViewDevice.setOnItemClickListener(itemClick);

        searchDevice.setOnQueryTextListener(new android.widget.SearchView.OnQueryTextListener() {

            @Override
            public boolean onQueryTextSubmit(String query) {
                return false;
            }

            @Override
            public boolean onQueryTextChange(String newText) {

                // Effectue la recherche
                if(newText != null && !newText.isEmpty()){
                    List<String> listSearchFoundDevice = new ArrayList<String>();

                    for(String item:listDeviceFound){
                        if(item.contains(newText))
                            listSearchFoundDevice.add(item);
                    }

                    // Ajoute affiche les résultats.
                    CustomListDevice adapter = new CustomListDevice(StartMenu.this,listSearchFoundDevice,listPower, listAddress);
                    listViewDevice.setAdapter(adapter);
                }
                else{
                    //if search text is null
                    //return default
                    CustomListDevice adapter = new CustomListDevice(StartMenu.this,listDeviceFound,listPower, listAddress);
                    listViewDevice.setAdapter(adapter);
                }
                return true;
            }
        });

    }

    @Override
    protected void onStart() {
        super.onStart();
        startService(new Intent(this, MessengerService.class));
        bindService(new Intent(this, MessengerService.class), mConnection, Context.BIND_AUTO_CREATE);
    }

    @Override
    protected void onResume() {
        super.onResume();
        cleanDeviceList();
        bindService(new Intent(this, MessengerService.class), mConnection, Context.BIND_AUTO_CREATE);

    }

    @Override
    protected  void onPause(){
        super.onPause();
        unbindService(mConnection);
    }



    @Override
    protected  void onDestroy(){
        super.onDestroy();
        unregisterReceiver(mReceiver);
    }


    private void addDeviceToList(String deviceName, int rssi, String deviceHardwareAddress){

        if(!listDeviceFound.contains(deviceName)) {
            listDeviceFound.add("s/n : " + deviceName);
            listPower.add(100 + rssi);
            listAddress.add(deviceHardwareAddress);
        }
        else{
            listPower.set(listDeviceFound.indexOf(deviceName), rssi);
        }

        CustomListDevice adapter = new CustomListDevice(StartMenu.this,listDeviceFound,listPower,listAddress);
        listViewDevice.setAdapter(adapter);
    }

    private void cleanDeviceList(){
        listAddress.clear();
        listDeviceFound.clear();
        listPower.clear();
    }


    private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();

            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                addDeviceToList(device.getName(),
                        intent.getShortExtra(BluetoothDevice.EXTRA_RSSI,Short.MIN_VALUE),
                        device.getAddress());
            }

            if (action.equals(BluetoothAdapter.ACTION_STATE_CHANGED)) {
                final int bluetoothState = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE,
                        BluetoothAdapter.ERROR);
                switch (bluetoothState) {
                    case BluetoothAdapter.STATE_ON:
                        break;
                }
            }
        }
    };


   /* @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.start_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }*/



    private ListView.OnItemClickListener itemClick = new AdapterView.OnItemClickListener() {
        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            Intent mainMenuIntent = new Intent(getContext(), mainMenu.class);

            String addressToConnect = listAddress.get(position);
            Toast.makeText(getApplicationContext(), addressToConnect, Toast.LENGTH_SHORT).show();


            Intent intent = new Intent();

            intent.putExtra("deviceAddress", addressToConnect);

            Message msg = Message.obtain(null, MessengerService.BLE_CONNECT, intent);

            try {
                mService.send(msg);
            } catch (RemoteException e) {
                e.printStackTrace();
            }

            startActivity(mainMenuIntent);
        }
    };

}


