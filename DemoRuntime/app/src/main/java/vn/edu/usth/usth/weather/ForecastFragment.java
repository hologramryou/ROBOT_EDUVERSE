package vn.edu.usth.usth.weather;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import androidx.fragment.app.Fragment;

public class ForecastFragment extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rootView = inflater.inflate(R.layout.forecastfragment, container, false);

        // Get the LinearLayout where the forecast items will be added
        LinearLayout forecastContainer = rootView.findViewById(R.id.forecast_container);

        // Example forecast data
        String[] days = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
        String[] descriptions = {"Partly Cloudy", "Showers", "Rain", "Scattered Showers", "Mostly Cloudy", "Partly Cloudy", "Thunderstorms"};
        int[] temps = {24, 25, 22, 22, 24, 25, 26};
        int[] icons = {R.drawable.sunny, R.drawable.showers, R.drawable.rain, R.drawable.scattered_showers, R.drawable.cloudy, R.drawable.sunny, R.drawable.thunderstorms};

        // Populate the forecast container dynamically
        for (int i = 0; i < days.length; i++) {
            View forecastItem = inflater.inflate(R.layout.forecast_item, forecastContainer, false);

            TextView dayView = forecastItem.findViewById(R.id.dayOfWeek);
            ImageView iconView = forecastItem.findViewById(R.id.weatherIcon);
            TextView descriptionView = forecastItem.findViewById(R.id.weatherDescription);
            TextView tempView = forecastItem.findViewById(R.id.temperatureRange);

            dayView.setText(days[i]);
            iconView.setImageResource(icons[i]);
            descriptionView.setText(descriptions[i]);
            tempView.setText(temps[i] + "C - " + (temps[i] + 7) + "C");

            forecastContainer.addView(forecastItem);
        }

        return rootView;
    }
}
