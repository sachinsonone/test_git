/****************************************************************
Date:		24.12.2013
Content:	This code is used for save live streaming in file
*****************************************************************/
    
    #include <iostream>
    #include <fstream>
    #include <cstdlib>
    #include <stdio.h>
    #include <stdlib.h>
    #include <vlc/vlc.h>
    #include <string.h>
    #include <iomanip>
    #include <sstream>
    #include <time.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <gtest/gtest.h>
    
    using std::cout;
    using std::endl;
    using namespace std;
    
    int main(int argc, char**argv)
    {
	
     ::testing::InitGoogleTest( &argc, argv );
     return RUN_ALL_TESTS();
     
     time_t start_time;
     time(&start_time);
     time_t end_time = start_time + 24 * 60 *3600;
     time_t current_time;
     
     double time_diff ;
     
     char start_date [80];
        
     char end_date [80];
     
     struct tm* timeinfo;
     
     if(argc > 3)
     {
	//this variable contain rtsp url
	string rtsp_url = argv[1];
	
	//this variable contain mux
	string mux = argv[2];
	
	//this variable contain destination folder path
	string destination = argv[3];
	
	//this variable contain extension of file like mp4, mpg
	string ext = argv[4];
	
	string cmd1;
	    
	libvlc_time_t i_time =  30;
	
	//create libvlc instance
	libvlc_instance_t * inst ;
	
	libvlc_media_player_t *m_pMediaPlayer;
	
	libvlc_media_t *pMedia;
	
	 //create libvlc instance 2
	libvlc_instance_t * inst1 ;
	
	libvlc_media_player_t *m_pMediaPlayer1;
	
	libvlc_media_t *pMedia1;
	
	int i = 0;
	
	string dir = "";
	
	string tmp_dir_path = "";
	
	while(1)
	   {
	   
		fflush(stdout);
	       
		time(&current_time);
		time_diff = difftime (end_time,current_time);
		time_diff = time_diff/60;
		time_diff = time_diff/60;
     
          	timeinfo = localtime(&current_time);
        
                strftime(start_date,80,"%Y-%m-%d",timeinfo);
		
		timeinfo->tm_mday += 1;
		
                strftime(end_date,80,"%Y-%m-%d",timeinfo);
		
		ostringstream tmp_ostring ;
		
		tmp_ostring << "/" << start_date << "_" << end_date ;
		
		DIR *pDir;
		
		pDir = opendir ((destination + (tmp_ostring.str())).c_str());
		
		if ( pDir == NULL )
		{
		   mkdir((destination + (tmp_ostring.str())).c_str(),0777);
		}
		
		(void) closedir (pDir);
		
		tmp_ostring << "/" << current_time;
		
		tmp_dir_path = destination + (tmp_ostring.str()) ;
		
		cmd1 = ":sout=#transcode{vcodec=mp4v,vfilter=canvas{width=800,height=600}}:std{access=file,mux=" + mux + ",dst=" + tmp_dir_path+"."+ ext + "}";  tmp_dir_path+"."+ ext + "}";  
	       
		if(i%2 == 0)
		{
		    inst = libvlc_new(argc, argv);
		    
		    m_pMediaPlayer = libvlc_media_player_new(inst);
		    
		    pMedia = libvlc_media_new_path(inst,rtsp_url.c_str());
		    
		    libvlc_media_player_set_media(m_pMediaPlayer, pMedia);
		    libvlc_media_add_option(pMedia, cmd1.c_str()) ;
		    libvlc_media_player_play(m_pMediaPlayer);
		    libvlc_media_player_set_time (m_pMediaPlayer,i_time);
		    libvlc_media_player_set_rate(m_pMediaPlayer,i_time);
		    
		    int j = 1;
		    bool tmp_flag;
		    while(j)
		    {
			tmp_flag = libvlc_media_player_is_playing(m_pMediaPlayer);
			if(tmp_flag)
			{
			  j= 0;  
			}
		    }
		 
		    if(i != 0)
		    {
			libvlc_media_player_stop (m_pMediaPlayer1);
			libvlc_media_player_release (m_pMediaPlayer1);
			libvlc_release (inst1);
		    }
		}
		else
		{
		    inst1 = libvlc_new(argc, argv);
		    
		    m_pMediaPlayer1 = libvlc_media_player_new(inst1);
		    pMedia1 = libvlc_media_new_path(inst1,rtsp_url.c_str());
		    
		    libvlc_media_player_set_media(m_pMediaPlayer1, pMedia1);
		    libvlc_media_add_option(pMedia1, cmd1.c_str()) ;
		    libvlc_media_player_play(m_pMediaPlayer1);
		    libvlc_media_player_set_time (m_pMediaPlayer1,i_time);
		    libvlc_media_player_set_rate(m_pMediaPlayer1,i_time);
		    
		    int j = 1;
		    bool tmp_flag;
		    while(j)
		    {
			tmp_flag = libvlc_media_player_is_playing(m_pMediaPlayer1);
			if(tmp_flag)
			{
			  j= 0;  
			}
		    }
		    libvlc_media_player_stop (m_pMediaPlayer);
		    libvlc_media_player_release (m_pMediaPlayer);
		    libvlc_release (inst);
		}
	        /*this will wait for 30 min */
		sleep (1800);
		
		i++;
	   }
	   
	      if(i%2 == 0)
	       {
		    /* Stop playing */
		    libvlc_media_player_stop (m_pMediaPlayer);
		    /* Free the media_player */
		    libvlc_media_player_release (m_pMediaPlayer);
		    /* Free the instance */
		    libvlc_release (inst);
	       }
	       else
	       {
		    /* Stop playing */
		    libvlc_media_player_stop (m_pMediaPlayer1);
		    /* Free the media_player */
		    libvlc_media_player_release (m_pMediaPlayer1);
		    /* Free the media_player */ 
		    libvlc_release (inst1);
	       }
    
	exit(0);
	return 0;
     }
    else
	    {
	       cout<<"Missing argument";
	       return 0;
	    }
    }
