package com.shpark.messagecheck4trance;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.telephony.SmsMessage;
import android.util.Log;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.Date;


/**
 * Created by SebineDEV on 2015-10-13.
 */
public class SMSReceiver extends BroadcastReceiver{

    static final String logTag = "SmsReceiver";
    static final String ACTION = "android.provider.Telephony.SMS_RECEIVED";
    private PropertyUtil property;

    Context con = ((MainActivity)MainActivity.context_main);

    public String ReadPhoneNumber(){
        String num = "010";
        SharedPreferences pref = con.getSharedPreferences("pref", Activity.MODE_PRIVATE);
        if((pref != null) && (pref.contains("phone"))){
            num = pref.getString("phone","010");
        }
        return num;
    }
    @Override
    public void onReceive(Context context, Intent intent) {
        if (intent.getAction().equals(ACTION)) {
            //Bundel 널 체크
            Bundle bundle = intent.getExtras();
            if (bundle == null) {
                return;
            }

            //pdu 객체 널 체크
            Object[] pdusObj = (Object[]) bundle.get("pdus");
            if (pdusObj == null) {
                return;
            }

            //message 처리
            SmsMessage[] smsMessages = new SmsMessage[pdusObj.length];
            for (int i = 0; i < pdusObj.length; i++) {
                smsMessages[i] = SmsMessage.createFromPdu((byte[]) pdusObj[i]);
                Log.d(logTag, "NEW SMS " + i + "th");
                Log.d(logTag, "DisplayOriginatingAddress : "
                        + smsMessages[i].getDisplayOriginatingAddress());
                Log.d(logTag, "DisplayMessageBody : "
                        + smsMessages[i].getDisplayMessageBody());
                Log.d(logTag, "EmailBody : "
                        + smsMessages[i].getEmailBody());
                Log.d(logTag, "EmailFrom : "
                        + smsMessages[i].getEmailFrom());
                Log.d(logTag, "OriginatingAddress : "
                        + smsMessages[i].getOriginatingAddress());
                Log.d(logTag, "MessageBody : "
                        + smsMessages[i].getMessageBody());
                Log.d(logTag, "ServiceCenterAddress : "
                        + smsMessages[i].getServiceCenterAddress());
                Log.d(logTag, "TimestampMillis : "
                        + smsMessages[i].getTimestampMillis());

//                Toast.makeText(context, smsMessages[i].getMessageBody(), 0).show();

                String address = smsMessages[i].getDisplayOriginatingAddress();

                long timestamp = smsMessages[i].getTimestampMillis();
                SimpleDateFormat formatter = new SimpleDateFormat("MM/dd HH:mm");
                String sdate = formatter.format(new Date(timestamp));
                String body = smsMessages[i].getDisplayMessageBody();

                String strSMS = String.format("번호:%s, 시간:%s, 내용:%s, ",address, sdate, body);
//                Toast.makeText(context, strSMS, 0).show();

                // 문자 보내기
                final SmsManager sms = SmsManager.getDefault();
                //property = new PropertyUtil();

                String strPhone = ReadPhoneNumber();
                sms.sendTextMessage(strPhone,null,strSMS,null,null);
            }
        }
    }
}
