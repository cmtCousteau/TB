package app.novaccess;

import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.text.GetChars;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class StartMenu extends AppCompatActivity {

    private List<String> listDeviceFound = new ArrayList<>();
    private List<Integer> listPower = new ArrayList<>();
    private List<String> listAddress = new ArrayList<>();

    private ListView listDevice;

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
            mBound = true;

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


    public Context getContext() {
        return (Context)this;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_start_menu);

        listDevice = (ListView) findViewById(R.id.listDevice);

        android.widget.SearchView searchDevice = (android.widget.SearchView) findViewById(R.id.searchDevice);

        CustomListDevice adapter = new CustomListDevice(StartMenu.this,listDeviceFound,listPower, listAddress);
        listDevice.setAdapter(adapter);

        listDevice.setOnItemClickListener(itemClick);

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
                    listDevice.setAdapter(adapter);
                }
                else{
                    //if search text is null
                    //return default
                    CustomListDevice adapter = new CustomListDevice(StartMenu.this,listDeviceFound,listPower, listAddress);
                    listDevice.setAdapter(adapter);
                }
                return true;
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        // Bind to the service

        startService(new Intent(this, MessengerService.class));

        bindService(new Intent(this, MessengerService.class), mConnection,
                Context.BIND_AUTO_CREATE);

        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
        registerReceiver(mReceiver, filter);
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected  void onPause(){
        super.onPause();
        unbindService(mConnection);
    }


    // Create a BroadcastReceiver for ACTION_FOUND.
    private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (BluetoothDevice.ACTION_FOUND.equals(action)) {
                // Discovery has found a device. Get the BluetoothDevice
                // object and its info from the Intent.

                BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

                int  rssi = intent.getShortExtra(BluetoothDevice.EXTRA_RSSI,Short.MIN_VALUE);
                String deviceName = device.getName();
                String deviceHardwareAddress = device.getAddress(); // MAC address

                if(!listDeviceFound.contains(deviceName)) {
                    listDeviceFound.add(deviceName);
                    listPower.add(100 + rssi);
                    listAddress.add(deviceHardwareAddress);
                    CustomListDevice adapter = new CustomListDevice(StartMenu.this,listDeviceFound,listPower,listAddress);
                    listDevice.setAdapter(adapter);
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


