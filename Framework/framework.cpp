#include "framework.h"
#include "../Game/boot.h"
#include "network.h"

Framework* Framework::System;

Framework::Framework()
{
#ifdef WRITE_LOG
	printf( "Framework: Startup: Allegro\n" );
#endif

	if( !al_init() )
	{
		printf( "Framework: Error: Cannot init Allegro\n" );
		quitProgram = true;
		return;
	}
	
	al_init_font_addon();
	if( !al_install_keyboard() || !al_install_mouse() || !al_init_primitives_addon() || !al_init_ttf_addon() || !al_init_image_addon() || !al_init_acodec_addon() || !al_install_audio() )
	{
		printf( "Framework: Error: Cannot init Allegro plugin\n" );
		quitProgram = true;
		return;
	}

#ifdef NETWORK_SUPPORT
	if( enet_initialize() != 0 )
	{
		printf( "Framework: Error: Cannot init enet\n" );
		quitProgram = true;
		return;
	}
#endif

#ifdef WRITE_LOG
	printf( "Framework: Startup: Variables and Config\n" );
#endif
	quitProgram = false;
  ProgramStages = new StageStack();
  framesToProcess = 0;
  Settings = new ConfigFile( "settings.cfg" );

	eventAllegro = al_create_event_queue();
	eventMutex = al_create_mutex();
	frameTimer = al_create_timer( 1.0 / FRAMES_PER_SECOND );

	System = this;
}

Framework::~Framework()
{
#ifdef WRITE_LOG
  printf( "Framework: Save Config\n" );
#endif
  SaveSettings();

#ifdef WRITE_LOG
  printf( "Framework: Clear stages\n" );
#endif
	if( ProgramStages != 0 )
	{
		// Just make sure all stages are popped and deleted
		ShutdownFramework();
	}

#ifdef WRITE_LOG
  printf( "Framework: Shutdown\n" );
#endif
	al_destroy_event_queue( eventAllegro );
	al_destroy_mutex( eventMutex );
	al_destroy_timer( frameTimer );
}

void Framework::Run()
{
#ifdef WRITE_LOG
  printf( "Framework: Run.Program Loop\n" );
#endif
  ProgramStages->Push( (Stage*)new BootUp() );

	while( !quitProgram )
	{
		ProcessEvents();
		while( framesToProcess > 0 )
		{
			if( ProgramStages->IsEmpty() )
			{
				break;
			}
			ProgramStages->Current()->Update();
			framesToProcess--;
		}
		if( !ProgramStages->IsEmpty() )
		{
			ProgramStages->Current()->Render();
		}
	}
}

void Framework::ProcessEvents()
{
#ifdef WRITE_LOG
  printf( "Framework: ProcessEvents\n" );
#endif

	if( ProgramStages->IsEmpty() )
  {
    quitProgram = true;
    return;
	}

	al_lock_mutex( eventMutex );

	while( eventQueue.size() > 0 && !ProgramStages->IsEmpty() )
	{
		Event* e;
		e = eventQueue.front();
		eventQueue.pop_front();
		switch( e->Type )
		{
			case EVENT_WINDOW_CLOSED:
				al_unlock_mutex( eventMutex );
				ShutdownFramework();
				return;
				break;
			case EVENT_WINDOW_RESIZE:
				resizeWindow( e->Data.Display.Resize.w, e->Data.Display.Resize.h );
				break;
			default:
				ProgramStages->Current()->EventOccurred( e );
				break;
		}
		delete e;
	}

	al_unlock_mutex( eventMutex );
}

void Framework::PushEvent( Event* e )
{
	SDL_LockMutex( eventMutex );
	eventQueue.push_back( e );
	SDL_UnlockMutex( eventMutex );
}

void Framework::ShutdownFramework()
{
#ifdef WRITE_LOG
  printf( "Framework: Shutdown Framework\n" );
#endif
  while( !ProgramStages->IsEmpty() )
  {
    delete ProgramStages->Pop();
  }
  quitProgram = true;
}

void Framework::SaveSettings()
{
  // Just to keep the filename consistant
  Settings->Save( "settings.cfg" );
}

void Framework::Display_Initialise()
{
#ifdef WRITE_LOG
  printf( "Framework: Initialise Display\n" );
#endif

#ifdef X86CPU
	int scrW = 800;
	int scrH = 480;
	bool scrFS = false;
#else
	int scrW = 800;
	int scrH = 480;
	bool scrFS = true;
#endif

	if( Settings->KeyExists( "Visual.ScreenWidth" ) )
  {
    Settings->GetIntegerValue( "Visual.ScreenWidth", &scrW );
	} else {
		Settings->SetIntegerValue( "Visual.ScreenWidth", scrW );
	}
	if( Settings->KeyExists( "Visual.ScreenHeight" ) )
  {
    Settings->GetIntegerValue( "Visual.ScreenHeight", &scrH );
	} else {
		Settings->SetIntegerValue( "Visual.ScreenHeight", scrH );
	}
	if( Settings->KeyExists( "Visual.FullScreen" ) )
  {
    Settings->GetBooleanValue( "Visual.FullScreen", &scrFS );
	} else {
		Settings->SetBooleanValue( "Visual.FullScreen", scrFS );
	}

}

void Framework::Display_Shutdown()
{
#ifdef WRITE_LOG
  printf( "Framework: Shutdown Display\n" );
#endif
}

int Framework::Display_GetWidth()
{
	return al_get_display_width( screen );
}

int Framework::Display_GetHeight()
{
	return al_get_display_height( screen );
}

void Framework::Display_SetTitle( std::string* NewTitle )
{
  SDL_WM_SetCaption( NewTitle->c_str(), 0 );
}

void Framework::Audio_Initialise()
{
#ifdef WRITE_LOG
  printf( "Framework: Initialise Audio\n" );
#endif
}

void Framework::Audio_Shutdown()
{
#ifdef WRITE_LOG
  printf( "Framework: Shutdown Audio\n" );
#endif
}

void Audio_PlayAudio( std::string Filename, bool Loop )
{
#ifdef WRITE_LOG
	printf( "Framework: Start audio file %s\n", Filename.c_str() );
#endif
}

void Audio_StopAudio()
{
#ifdef WRITE_LOG
  printf( "Framework: Stop audio\n" );
#endif
}

