package com.shpark.messagecheck4trance;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class BootUpReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		Intent i = new Intent(context,StatusService.class);
		i.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		context.startService(i);
	}

}
