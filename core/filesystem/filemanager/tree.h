#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE tree :
      virtual public ::userfs::tree,
      virtual public ::filemanager::impact
   {
   public:


      enum e_message
      {

         MessageMainPost,

      };

      enum EMessageMainPost
      {

         MessageMainPostCreateImageListItemRedraw,

      };

      enum e_step
      {
         step_start,
         step_image_visible,
         step_has_subdir_visible,
         step_image_hidden,
         step_has_subdir_hidden,
         step_end,
      };



      context_menu            m_contextmenu;


#ifdef WINDOWS_DESKTOP
      map < EFolder, EFolder, IShellFolder *, IShellFolder *> m_mapFolder;
#endif


      tree();
      virtual ~tree();


      virtual ::estatus initialize_filemanager_tree(document * pdocument);


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual void _001InsertColumns() override;

      void _001OnTimer(::timer * ptimer) override;


      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;


      virtual void _017OpenFolder(__pointer(::file::item) pitem, const ::action_context & action_context) override;

#ifdef WINDOWS_DESKTOP

      i32 MapToCSIDL(EFolder efolder);

      IShellFolder * _001GetFolder(EFolder efolder);

#endif


      void TakeAnimationSnapshot();
      virtual void StartAnimation();
      DECL_GEN_SIGNAL(_001OnMainPostMessage);
      void GetSelectedFilePath(string_array & stra);
      virtual bool _001IsTranslucent() override;


      virtual void browse_sync(const ::action_context & action_context) override;
      virtual void knowledge(const ::file::path & pathUser, const ::action_context & action_context,bool bOnlyParent = false);
      //virtual void filemanager_tree_insert(const ::file::path & strPath,::file::listing & listingUser, ::file::listing & listingFinal, const ::action_context & action_context,bool bOnlyParent = false, bool bVoidTreeDataChangeEvent = true);
      void _017EnsureVisible(const ::file::path & pathUser, const ::action_context & action_context);



      void RenameFile(i32 iLine, string & str, const ::action_context & action_context);

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShellCommand);


      virtual void on_merge_user_tree(::user::tree * pusertree) override;
      virtual void on_bind_user_tree(::user::tree * pusertree) override;


   };


} // namespace filemanager



