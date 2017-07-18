// Inspiré de : https://www.learn2crack.com/2013/10/android-custom-listview-images-text-example.html


package app.novaccess;

import android.widget.ArrayAdapter;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.List;


public class CustomListDevice extends ArrayAdapter<String> {

    private final Activity context;
    private final List<String> deviceNameList;
    private final List<Integer> deviceRssi;
    private final List<String> deviceAddressList;

    public CustomListDevice(Activity context, List<String> deviceNameList, List<Integer> rssiList, List<String> addressList) {

        super(context, R.layout.list_item_devices, deviceNameList);
        this.context = context;
        this.deviceNameList = deviceNameList;
        this.deviceRssi = rssiList;
        this.deviceAddressList = addressList;
    }

    @Override
    public View getView(int position, View view, ViewGroup parent) {

        LayoutInflater inflater = context.getLayoutInflater();
        View rowView = inflater.inflate(R.layout.list_item_devices, null, true);

        // Réupère les différents TextView présents dans la vue.
        TextView deviceName = (TextView) rowView.findViewById(R.id.deviceName);
        TextView deviceAddress = (TextView) rowView.findViewById(R.id.deviceAddress);
        ProgressBar receptionPower = (ProgressBar) rowView.findViewById(R.id.rssi);

        // Ajoute le texte aux différents TextView.
        deviceName.setText("s/n : " + deviceNameList.get(position));
        deviceAddress.setText(deviceAddressList.get(position));
        receptionPower.setProgress(deviceRssi.get(position));

        return rowView;
    }
}
