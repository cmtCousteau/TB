package app.novaccess;

import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class resourcesIndexMenu extends AppCompatActivity {


    List<String> listResourcesName = new ArrayList<>();
    List<String> listResourcesValue = new ArrayList<>();
    ListView listResources;

    int i = 0;

    public Context getContext() {
        return (Context)this;
    }

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

            Message msg = Message.obtain(null, MessengerService.READ_VALUE, 0, 0);
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.resources_index_menu);

        listResources = (ListView) findViewById(R.id.listResources);

        Intent intent = new Intent(this, MessengerService.class);
        bindService(intent,mConnection,Context.BIND_AUTO_CREATE);


        listResourcesName.add("Voltage :");
        listResourcesValue.add("230v");

        listResourcesName.add("Courant :");
        listResourcesValue.add("5A");

        listResourcesName.add("Cosphi :");
        listResourcesValue.add("12");

        listResourcesName.add("Fréquence :");
        listResourcesValue.add("200 Hz");

        listResourcesName.add("Puissance Aggrégée :");
        listResourcesValue.add("300 kWh");

        CustomListResources adapter = new CustomListResources(resourcesIndexMenu.this,listResourcesName,listResourcesValue);
        listResources.setAdapter(adapter);

        IntentFilter filter = new IntentFilter("CHARACTERISTIC_READ");
        registerReceiver(mReadCharacteristicReiver, filter);

    }

    @Override
    protected  void onPause(){
        super.onPause();
        unbindService(mConnection);
        unregisterReceiver(mReadCharacteristicReiver);
    }

    // Create a BroadcastReceiver for ACTION_FOUND.
    private final BroadcastReceiver mReadCharacteristicReiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            String value = intent.getStringExtra("value");

            listResourcesName.add("Test :");
            listResourcesValue.add(value);

            Toast.makeText(getApplicationContext(), "Nombre appel : " + ++i, Toast.LENGTH_SHORT).show();

            CustomListResources adapter = new CustomListResources(resourcesIndexMenu.this,listResourcesName,listResourcesValue);
            listResources.setAdapter(adapter);
        }
    };
}
