package com.shpark.messagecheck4trance;

import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;

import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import android.content.ContentResolver;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
//import android.os.Bundle;
//import android.support.design.widget.FloatingActionButton;
//import android.support.design.widget.Snackbar;
//import android.support.v7.app.AppCompatActivity;
//import android.support.v7.widget.Toolbar;
import android.telephony.SmsManager;
import android.util.Log;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import android.content.ComponentName;

import java.text.SimpleDateFormat;
import java.util.Date;

public class MainActivity extends AppCompatActivity {
    EditText etPhoneNumber;
    Button btSave;
    private PropertyUtil property;
    private Intent intent;
    public ComponentName mService;

    public static Context context_main;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        context_main = this;

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        //tvTitle = (TextView) findViewById(R.id.textView1);
        //tv.append(readSMSMessage());

        etPhoneNumber   = (EditText) findViewById(R.id.editText);
        btSave          = (Button) findViewById(R.id.button);
        //property        = new PropertyUtil();

        String strData = ReadPhoneNumber();//property.getProperty("phone");
        if(strData != null)
            etPhoneNumber.setText(strData);

        btSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SavePhoneNumber();
                //property.setProperty("phone", etPhoneNumber.getText().toString());
                //property.storeProperty("phone");
                //Toast.makeText(MainActivity.this, "저장되었습니다.", 0).show();
            }
        });

        intent=new Intent(this,StatusService.class);
        // service start
        mService = startService(intent);	// 여러번 재시작해도 중첩되지 않음

    }

    public void SavePhoneNumber(){
        SharedPreferences pref = getSharedPreferences("pref", Activity.MODE_PRIVATE);
        SharedPreferences.Editor editor = pref.edit();
        editor.putString("phone",etPhoneNumber.getText().toString());
        editor.commit();
    }
    public String ReadPhoneNumber(){
        String num = "010";
        SharedPreferences pref = getSharedPreferences("pref", Activity.MODE_PRIVATE);
        if((pref != null) && (pref.contains("phone"))){
            num = pref.getString("phone","010");
            etPhoneNumber.setText(num);
        }
        return num;
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
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
    }




    public String readSMSMessage()
    {
        Uri allMessage = Uri.parse("content://sms/inbox");
        ContentResolver cr = getContentResolver();
        Cursor c = cr.query(allMessage,
                new String[]{"_id", "thread_id", "address", "person", "date", "body",
                        "protocol", "read", "status", "type", "reply_path_present",
                        "subject", "service_center", "locked", "error_code", "seen"},
                "read = 0", null,
                "date DESC");
        String strSMS ="";
        int count=0;
        while  (c.moveToNext()) {
            long messageId = c.getLong(0);
            long threadId = c.getLong(1);
            String address = c.getString(2);
            long contactId = c.getLong(3);
            String contactId_string = String.valueOf(contactId);
            long timestamp = c.getLong(4);
            SimpleDateFormat formatter = new SimpleDateFormat("MM/dd HH:mm");
            String sdate = formatter.format(new Date(timestamp));
            String body = c.getString(5);

            long protocol = c.getLong(6);
            long read     = c.getLong(7);
            String sRead = "읽음";
            if(read == 0)
            {
                sRead = "읽지 않음";
            }
            long status   = c.getLong(8);
            long type   = c.getLong(9);
            String reply_path = c.getString(10);
            String subject = c.getString(11);
            String servicecenter = c.getString(12);
            long locked = c.getLong(13);
            long error = c.getLong(14);
            long seen = c.getLong(15);

            strSMS = String.format("%s, 번호:%s, " +
                            "시간:%s, 내용:%s, ",
                    sRead ,address,
                    sdate, body);

            // 문자 보내기
            final SmsManager sms = SmsManager.getDefault();
            //sms.sendTextMessage("01088167623",null,strSMS,null,null);

            Log.d("maluchi", ++count + "st, Message: " + strSMS);

            //tv.append(strSMS);
        }

        return strSMS;
    }
/*
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
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
    }

 */
}
