#pragma once


   namespace experience
   {


      namespace aura
      {


         class CLASS_DECL_APP_EXPERIENCE_CORE experience:
            public ::experience::experience
         {
         public:


            


            experience();
            virtual ~experience();


            virtual ::estatus initialize(::layered * pobjectContext) override;


            virtual void update() override;


            virtual void get_frame_list(string_array & stra) override;


            virtual ::experience::frame * experience_get_frame(const char * pszSchema) override;


         };



      } // namespace aura


   } // namespace experience



