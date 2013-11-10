//---------------------------------------------------------------------------

#ifndef trb_paramsH
#define trb_paramsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TTrbOptions : public TForm
{
__published:    // IDE-managed Components
    TCheckBox *OneRow;
    TLabeledEdit *FileName;
    TButton *SetFile;
    TCheckBox *ActiveDelimiter;
    TEdit *Count;
    TLabel *Label1;
    TBitBtn *ok;
    TBitBtn *cancel;
    TSaveDialog *SD;
    TLabeledEdit *Receiver;
    TLabeledEdit *Organization_;
    void __fastcall SetFileClick(TObject *Sender);
    void __fastcall okClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:    // User declarations
public:        // User declarations
    __fastcall TTrbOptions(TComponent* Owner);
    String save_to_file;
    String file_ext;
    String Organization;
    String MatReceiver;
    bool trim_file;
    int  lists_in_file;
};
#endif
