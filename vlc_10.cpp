#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <vlc/vlc.h>
#include <string.h>
#include <iomanip>
#include <sstream>



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
    //cout<<"process";
    check_player_working(m_pMediaPlayer);
}


int main(int argc, char**argv)
{

 if(argc > 3)
 {
        
	string input_stream = argv[1];
        
        string mux = argv[2];

        string dst = argv[3];
        
        string ext = argv[4];

        char dbl_quote = '"'; 

        string cmd1;
	    
        
       
       libvlc_time_t i_time =  30;
       libvlc_instance_t * inst ;
       libvlc_media_player_t *m_pMediaPlayer;
       libvlc_media_t *pMedia;
       
       libvlc_instance_t * inst1 ;
       libvlc_media_player_t *m_pMediaPlayer1;
       libvlc_media_t *pMedia1;
       
       
       int i = 0;
       for(i =0;i<5;i++)
       {
       
            fflush(stdout);
           
            string tmp = "1" ;
       
            std::ostringstream convert_string;
            
            convert_string << i+1;
            
            tmp = convert_string.str();
            
            //cmd1 = ":sout=#duplicate{dst=nodisplay,dst=std{codec=mlaw,pid-video=68,pid-audio=70,maxrate=1500,access=file,mux=" + mux + ",dst=" + dst+tmp+"."+ ext + "}}sout-record-";  
     
            cmd1 = ":sout=#duplicate{dst=nodisplay,dst=std{codec=mlaw,pid-video=68,pid-audio=70,maxrate=1500,access=file,mux=" + mux + ",dst=" + dst+tmp+"."+ ext + "}}";  
     
           
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
            //check_player_working(m_pMediaPlayer);
            
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
            
            //check_player_working(m_pMediaPlayer1);
            
            
            libvlc_media_player_stop (m_pMediaPlayer);
            libvlc_media_player_release (m_pMediaPlayer);
            libvlc_release (inst);
           }
            
     
            sleep (100);
            //sleep (100); /* Let it play a bit */
       }
       
          if(i%2 == 0)
           {
            /* Stop playing */
               libvlc_media_player_stop (m_pMediaPlayer);
       
               /* Free the media_player */
               libvlc_media_player_release (m_pMediaPlayer);
       
               libvlc_release (inst);
           }
           else
           {
           
            libvlc_media_player_stop (m_pMediaPlayer1);
    
            /* Free the media_player */
            libvlc_media_player_release (m_pMediaPlayer1);
    
            libvlc_release (inst1);
           }

	cout << "ready" << endl;
	//int i;
	//cin >> i;
        exit(0);
	return 0;

	
 }
else
	{
           cout<<"Missing argument";
	}

}
