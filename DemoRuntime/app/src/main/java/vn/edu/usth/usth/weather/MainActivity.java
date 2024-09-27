package anhluu.robot.runtime.demo;

import android.annotation.SuppressLint;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class MainActivity extends AppCompatActivity {

    private EditText messageEditText;
    private Button sendButton;
    private Button foward, left, right, back, up, down;

    @SuppressLint({"WrongViewCast", "MissingInflatedId"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        messageEditText = findViewById(R.id.messageEditText);
        sendButton = findViewById(R.id.sendButton);
        foward = findViewById(R.id.foward);
        left = findViewById(R.id.left);
        right = findViewById(R.id.right);
        back = findViewById(R.id.back);
        up = findViewById(R.id.up);
        down = findViewById(R.id.down);

        sendButton.setOnClickListener(v -> {
            String message = messageEditText.getText().toString();
            if (!message.isEmpty()) {
                new SendPostRequestTask().execute(message);
            } else {
                Toast.makeText(MainActivity.this, "Please enter a message", Toast.LENGTH_SHORT).show();
            }
        });

        // Set up touch listeners for the buttons
        setButtonTouchListener(foward, "W");
        setButtonTouchListener(left, "A");
        setButtonTouchListener(right, "D");
        setButtonTouchListener(back, "S");
        setButtonTouchListener(up, "U");
        setButtonTouchListener(down, "I");
    }

    private void setButtonTouchListener(Button button, String downMessage) {
        button.setOnTouchListener((v, event) -> {
            switch (event.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    // Send the corresponding message when the button is pressed
                    new SendPostRequestTask().execute(downMessage);
                    return true;
                case MotionEvent.ACTION_UP:
                    // Send "F" when the button is released
                    new SendPostRequestTask().execute("F");
                    return true;
            }
            return false;
        });
    }

    private class SendPostRequestTask extends AsyncTask<String, Void, String> {

        @Override
        protected String doInBackground(String... params) {
            String message = params[0];
            HttpURLConnection urlConnection = null;
            try {
                URL url = new URL("http://192.168.4.1/post"); // Replace with the IP of your ESP8266
                urlConnection = (HttpURLConnection) url.openConnection();
                urlConnection.setRequestMethod("POST");
                urlConnection.setRequestProperty("Content-Type", "text/plain");
                urlConnection.setDoOutput(true);

                // Send the POST request
                OutputStream os = urlConnection.getOutputStream();
                os.write(message.getBytes());
                os.flush();
                os.close();

                // Check the response code
                int responseCode = urlConnection.getResponseCode();
                if (responseCode == HttpURLConnection.HTTP_OK) {
                    return "Message sent successfully";
                } else {
                    return "Failed to send message. Response code: " + responseCode;
                }
            } catch (Exception e) {
                e.printStackTrace();
                return "Error: " + e.getMessage();
            } finally {
                if (urlConnection != null) {
                    urlConnection.disconnect();
                }
            }
        }

        @Override
        protected void onPostExecute(String result) {
            Toast.makeText(MainActivity.this, result, Toast.LENGTH_LONG).show();
        }
    }
}
