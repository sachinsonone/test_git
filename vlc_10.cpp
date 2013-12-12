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
    
    
    
    using std::cout;
    using std::endl;
    
    using namespace std;
    
    
    bool check_player_working(libvlc_media_player_t *m_pMediaPlayer)
    {
	
	bool tmp_flag = libvlc_media_player_is_playing(m_pMediaPlayer);
	
	if(tmp_flag)
	{
	    cout<<"stop";
	    return true;
	}
	check_player_working(m_pMediaPlayer);
    }
    
    
    int total_hours = 36;
    
    int interval = 24 ;
    
    
    int main(int argc, char**argv)
    {
	
      
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
	    
	    string input_stream = argv[1];
	    
	    string mux = argv[2];
    
	    string dst = argv[3];
	    
	    string ext = argv[4];
    
	    char dbl_quote = '"'; 
    
	    string cmd1;
		
	    //this for instance 1
	    libvlc_time_t i_time =  30;
	    
	    libvlc_instance_t * inst ;
	    
	    libvlc_media_player_t *m_pMediaPlayer;
	    
	    libvlc_media_t *pMedia;
	    
	    
	     //this for instance 2
	    libvlc_instance_t * inst1 ;
	    
	    libvlc_media_player_t *m_pMediaPlayer1;
	    
	    libvlc_media_t *pMedia1;
	   
	   
	   int i = 0;
	   
	   
	   string dir = "";
	   
	   string tmp_dir_path = "";
	   
	   for(i =0;i>-1;i++)
	   {
	   
		fflush(stdout);
	       
		string tmp = "1" ;
	   
		time(&current_time);
		
		time_diff = difftime (end_time,current_time);
		time_diff = time_diff/60;
		time_diff = time_diff/60;
     
                
		timeinfo = localtime(&current_time);
        
                strftime(start_date,80,"%Y-%m-%d",timeinfo);
		
		timeinfo->tm_mday += 1;
		
                time_t tmp_time = mktime(timeinfo);
		
		strftime(end_date,80,"%Y-%m-%d",timeinfo);
		
		ostringstream tmp_ostring ;
		
		
		tmp_ostring << "/" << start_date << "_" << end_date ;
		
		DIR *pDir;
		
		
		pDir = opendir ((dst + (tmp_ostring.str())).c_str());
		
		
		if ( pDir == NULL )
		{
		   mkdir((dst + (tmp_ostring.str())).c_str(),0777);
		}
		
		(void) closedir (pDir);
		
		tmp_ostring << "/" << current_time;
		
		tmp_dir_path = dst + (tmp_ostring.str()) ;
		
		
		//cmd1 = ":sout=#stream_out_duplicate{dst=nodisplay,dst=std{codec=mlaw,pid-video=68,pid-audio=70,maxrate=1500,access=file,mux=" + mux + ",dst=" + tmp_dir_path+"."+ ext + "}}";  
	 
	        cmd1 = ":sout=#transcode{vcodec=mp4v,vfilter=canvas{width=800,height=600}}:std{access=file,mux=" + mux + ",dst=" + tmp_dir_path+"."+ ext + "}";  
	       
		if(i%2 == 0)
		{
		    inst = libvlc_new(argc, argv);
		    
		    m_pMediaPlayer = libvlc_media_player_new(inst);
		    
		    pMedia = libvlc_media_new_path(inst,input_stream.c_str());
		    
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
		    
		    pMedia1 = libvlc_media_new_path(inst1,input_stream.c_str());
		    
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
		//sleep (100);
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
