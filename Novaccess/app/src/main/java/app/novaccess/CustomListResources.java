// Inspiré de : https://www.learn2crack.com/2013/10/android-custom-listview-images-text-example.html


package app.novaccess;

import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.List;


public class CustomListResources extends ArrayAdapter<String> {

    private final Activity context;
    private final List<String> resourcesNameList;
    private final List<String> resourcesValueList;

    public CustomListResources(Activity context, List<String> resourcesNameList, List<String> resourcesValueList) {

        super(context, R.layout.list_item_resources, resourcesNameList);
        this.context = context;
        this.resourcesNameList = resourcesNameList;
        this.resourcesValueList = resourcesValueList;

    }

    @Override
    public View getView(int position, View view, ViewGroup parent) {

        LayoutInflater inflater = context.getLayoutInflater();
        View rowView = inflater.inflate(R.layout.list_item_resources, null, true);

        TextView resourceName = (TextView) rowView.findViewById(R.id.resourceName);
        TextView resourceValue = (TextView) rowView.findViewById(R.id.deviceName);

        resourceName.setText(resourcesNameList.get(position));
        resourceValue.setText(resourcesValueList.get(position));

        return rowView;
    }
}
