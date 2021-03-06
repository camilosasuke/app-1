#pragma once


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {

         class CLASS_DECL_MUSIC_MIDI_MMSYSTEM out :
            virtual public ::music::midi::out
         {
         public:


            HMIDIOUT       m_hmidiout;


            out(::layered * pobjectContext);
            virtual ~out();


            virtual ::estatus     open();
            virtual ::estatus     close();

            ::estatus     send_short_message(::music::midi::enum_type etype, int iChannel, int iData1, int iData2);

         };


      } // namespace mmsystem


   } // namespace midi


} // namespace music




