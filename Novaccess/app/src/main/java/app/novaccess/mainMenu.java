package app.novaccess;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class mainMenu extends AppCompatActivity {

    Messenger mService = null;

    private ServiceConnection mConnection = new ServiceConnection() {
        // Appelé lorsque l'on est connecté au service.
        public void onServiceConnected(ComponentName className, IBinder service) {

            mService = new Messenger(service);

            Message msg = Message.obtain(null, MessengerService.GET_CONNECTED_BLE_ADDRESS, 0, 0);
            try {
                mService.send(msg);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

        // Appelé lors de la déconnexion du service.
        public void onServiceDisconnected(ComponentName className) {
            mService = null;
        }
    };

    public Context getContext() {
        return (Context)this;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_menu);

        Button btnResourcesIndex = (Button) findViewById(R.id.btnResourcesIndex);
        btnResourcesIndex.setOnClickListener(btnResourcesIndexClick);

        Button btnParametersIndex = (Button) findViewById(R.id.btnParametersIndex);
        btnParametersIndex.setOnClickListener(btnParametersIndexClick);

        Button btnDisconnect = (Button) findViewById(R.id.btnDisconnect);
        btnDisconnect.setOnClickListener(btnDisconnectClick);
    }

    @Override
    protected  void onResume(){
        super.onResume();
        Intent intent = new Intent(this, MessengerService.class);
        bindService(intent,mConnection,Context.BIND_AUTO_CREATE);
    }

    @Override
    protected  void onPause(){
        super.onPause();
        unbindService(mConnection);
    }

    @Override
    public void onBackPressed() {

        Message msg = Message.obtain(null, MessengerService.BLE_DISCONNECT, 0, 0);
        try {
            mService.send(msg);
        } catch (RemoteException e) {
            e.printStackTrace();
        }

        super.onBackPressed();
    }


    private  View.OnClickListener btnResourcesIndexClick = new View.OnClickListener(){

        @Override
        public void onClick(View v) {
            Intent resourcesIndexMenuIntent = new Intent(getContext(), resourcesIndexMenu.class);
            startActivity(resourcesIndexMenuIntent);
        }
    };


    private  View.OnClickListener btnDisconnectClick = new View.OnClickListener(){

        @Override
        public void onClick(View v) {

            Message msg = Message.obtain(null, MessengerService.BLE_DISCONNECT, 0, 0);
            try {
                mService.send(msg);
            } catch (RemoteException e) {
                e.printStackTrace();
            }

            Intent IntentStartMenuIntent = new Intent(getContext(), StartMenu.class);
            startActivity(IntentStartMenuIntent);
        }
    };

    private  View.OnClickListener btnParametersIndexClick = new View.OnClickListener(){

        @Override
        public void onClick(View v) {

            Intent IntentStartMenuIntent = new Intent(getContext(), ParametersIndex.class);
            startActivity(IntentStartMenuIntent);
        }
    };
}
