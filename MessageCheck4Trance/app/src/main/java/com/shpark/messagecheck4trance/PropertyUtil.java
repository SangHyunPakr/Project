package com.shpark.messagecheck4trance;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Properties;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Environment;
import android.provider.ContactsContract;
import android.util.Log;

/**
 * 
 * @author sebine_Win7
 * @ 설정을 저장하기 위한 property
 * @ 
 */
public class PropertyUtil {
	private static final String LOG_TAG = "[LOG_ANDROID]";
	 /**
     * PropertyUtil 객체
     */
     private static PropertyUtil m_propertyUtil; /**
     * 프로퍼티 파일명
     */
    private final String PROPERTIY_PATH  = Environment.getExternalStorageState() +"/com.shpark.message4trance/files";//"/data/data/com.shpark.message4trance/f.properties";


    private final String PROPERTIY_FILE  = "/f.properties";

     /**
     * file
     */
     private static File m_fileDir   = null;
     private static File m_profile   = null;
     /**
     * file input stream
     */
     private static FileInputStream m_fis  = null;
     /**
     * file output stream
     */
     private static FileOutputStream m_fos  = null;
     /**
     * properties
     */
     private static Properties m_pros  = null;



     
     PropertyUtil() {
         m_fileDir = new File(PROPERTIY_PATH); //프로퍼티 경로 객체 생성
         try {
             if (!m_fileDir.exists())
                 if(m_fileDir.mkdir())
                     Log.d(LOG_TAG, "디렉토리 생성");
                 else
                     Log.d(LOG_TAG, "디렉토리 생성 실패 ");
         }catch(Exception e){
             e.printStackTrace();
             Log.d(LOG_TAG, "dir 생성 실패 -> " +e.getMessage());
         }
         m_profile = new File(PROPERTIY_PATH+PROPERTIY_FILE); //프로퍼티 파일 객체 생성
         m_pros = new Properties();
         try {
             //프로퍼티 파일이 없는 경우 파일을 새로 생성한다.
             if(!m_profile.exists())
                 m_profile.createNewFile(); //프로퍼티 파일 입력 스트림
                 m_fis = new FileInputStream(m_profile);
                 //프로퍼티 파일 출력 스트림
                 m_fos = new FileOutputStream(m_profile, true); //프로퍼티 파일을 메모리로 로드한다.
                 m_pros.load(m_fis);
         } catch(IOException e) {
             e.printStackTrace();
             Log.d(LOG_TAG, "Property File 생성 및 로드 실패 -> " +e.getMessage());
         }
     }
     
     public synchronized static PropertyUtil getInstance() {
         if (m_propertyUtil == null) {
             m_propertyUtil = new PropertyUtil();
         }
         return m_propertyUtil;
     }
     
     public String getProperty(String key) {
         return m_pros.getProperty(key);
     }
     
     public void setProperty(String key, String value) {
         m_pros.setProperty(key, value);
     }
     
     public void storeProperty(String comment) {
         try{
             m_pros.store(m_fos, comment);
         } catch(Exception e) {
             e.printStackTrace();
             Log.d(LOG_TAG, "Property File 저장 실패 -> " +e.getMessage());
         }
     }
}
