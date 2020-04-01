package com.shpark.messagecheck4trance;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.IBinder;
//import android.support.annotation.Nullable;
import android.util.Log;

import android.app.PendingIntent;
import android.app.AlarmManager;

import java.io.PrintWriter;
import java.io.StringWriter;

/**
 * Created by DEVx64 on 2016-01-07.
 */
public class StatusService extends Service {

    static final boolean IS_DEBUG = false;
    private static final String TAG = "Mytag";
    private static final int TIMER_PERIOD = 10*1000;

//    @Nullable
    //create
    private Intent intent;
    private PendingIntent alarmPI;
    private PropertyUtil property;
    //on start command
    private BroadcastReceiver broadcastReceiver;
    private Intent returnRegisterIntent = null;
    public IntentFilter filter = new IntentFilter();

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {

        unregisterReceiver(broadcastReceiver);
        super.onDestroy();
    }

    @Override
    public void onCreate() {
        super.onCreate();

//        nManagerNoti=(NotificationManager)getSystemService(NOTIFICATION_SERVICE);

        try{
            intent=new Intent(getBaseContext(),StatusService.class);
            alarmPI=PendingIntent.getService(getBaseContext(),0,intent,PendingIntent.FLAG_UPDATE_CURRENT);
            AlarmManager am = (AlarmManager)getSystemService(ALARM_SERVICE);
            // 비 정확성
            am.setInexactRepeating(AlarmManager.RTC, System.currentTimeMillis(), TIMER_PERIOD, alarmPI);
            // 정확성
            //am.setRepeating(AlarmManager.RTC, System.currentTimeMillis(), TIMER_PERIOD, alarmPI);

            broadcastReceiver = new SMSReceiver();
            returnRegisterIntent=registerReceiver(broadcastReceiver, filter);

        }catch (Exception e) {
            StringWriter sw = new StringWriter();
            e.printStackTrace(new PrintWriter(sw));
            if(IS_DEBUG){
                String exceptionAsStrting = sw.toString();
                Log.e("errorCreate", exceptionAsStrting);
            }
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        // TODO Auto-generated method stub
        //if(intent == null)
        //{
            try{
                if(IS_DEBUG)
                    Log.d(TAG,"command start service id="+startId);

                broadcastReceiver = new SMSReceiver();
                returnRegisterIntent=registerReceiver(broadcastReceiver, filter);

            }catch (Exception e) {
                StringWriter sw = new StringWriter();
                e.printStackTrace(new PrintWriter(sw));

                if(IS_DEBUG){
                    String exceptionAsStrting = sw.toString();
                    Log.e("onStartCommand", exceptionAsStrting);
                }
            }
        //}
        //return super.onStartCommand(intent, flags, startId);
        return START_STICKY;				//null 인텐트로 onStartCommand()호출	//갤스
        //return START_NOT_STICKY;			//stop service
        //return START_REDELIVER_INTENT;	//인텐트가 전달	갤스(않좋음)
    }


}
