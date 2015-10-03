unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ADODB, StdCtrls, adoint,
  rfUnit, rfReq, ExtCtrls, ComCtrls, JvTrayIcon, JvComponentBase, JvGIF;

type
	TConn=TADOConnection;

type
	TRst=_Recordset;

type
  TForm1 = class(TForm)
    Button7: TButton;
    Button8: TButton;
    Button9: TButton;
    Button10: TButton;
    Button11: TButton;
    Button13: TButton;
    Button14: TButton;
    Timer1: TTimer;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    DT1: TDateTimePicker;
    DT2: TDateTimePicker;
    Button1: TButton;
    Button2: TButton;
    Panel1: TPanel;
    Panel2: TPanel;
    Button3: TButton;
    M1: TMemo;
    Button4: TButton;
    Label5: TLabel;
    JvTrayIcon1: TJvTrayIcon;
    Edit5: TEdit;
    Button5: TButton;
    Panel3: TPanel;
    Label6: TLabel;
    Panel4: TPanel;
    Image1: TImage;
    Image2: TImage;
    Image3: TImage;
    procedure AppRestart;
    procedure unreg;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure Button13Click(Sender: TObject);
    procedure Button14Click(Sender: TObject);
    procedure Button15Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure Button11Click(Sender: TObject);
    procedure JvTrayIcon1DblClick(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button12Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure FormCloseQuery(Sender: TObject; var CanClose: Boolean);
    procedure FormDestroy(Sender: TObject);
    procedure Edit5KeyPress(Sender: TObject; var Key: Char);
	private
//		LogNum,User,Password:longint;
		conn:TConn;
		function connect(user:integer;password:integer): boolean;
		{ Private declarations }
  public
    { Public declarations }
    var Nachsum: real;
    procedure SetParams;
  end;


var
  Form1: TForm1;
  Psw: String;
  conn:TConn ;
  lrst:TRst;
  proci: Integer;//IDispatch;
 MyMutex: THandle;

  
implementation

uses HcTLB_TLB, comobj, oledb;

{$R *.dfm}

procedure TForm1.AppRestart;
var
 FullProgPath: PChar;
begin
 FullProgPath:=PChar(Application.ExeName);
 CloseHandle(MyMutex)    ;
 WinExec(FullProgPath,SW_SHOW);
 Application.Terminate;
end;

// Расшифровка электронной ленты
//		$00:result:='Bad: Удаленная запись';
//		$10:result:='Void: Диапазон отмены';
//		$11:result:='Qty: Количество проданного товара';
//		$13:result:='Rasp: Расплата';
//		$14:result:='InOut: Внос/вынос';
//		$15:result:='Prom: Промежуточный итог';
//		$1C:result:='Comm: Комментарий';
//		$1D:result:='Check: Конец чека';
//		$1E:result:='Smen: Начало смены';
//		$1F:result:='ZRep: Обнуляющий отчет';
//		$2C:result:='Prod: Продажа';
//		$2D:result:='Nac: Скидка/наценка';
//		$31:result:='ZDep: ';
//		$32:result:='ZTov: ';
//		$33:result:='ZOpr: ';
//		$34:result:='ZTim: ';
//		$35:result:='ZLnt: ';
//		$36:result:='RepFsk: ';
//		$51:result:='PayOff: Выплата';
//		$60:result:='Code: Код товара';
//		$61:result:='Name: Имя товара';
//		$cc:result:='NoFsChk: Не фискальный чек';
//		$ee:result:='Offset: Лента просквизирована';
//		$ff:result:='Empty: Пустая запись';


procedure Tform1.unreg;
begin
  conn.Close;
  conn.Free;
  Label1.Caption:='Кассир не зарегистрирован';
  Label3.Show;
  Label4.Show;
  Edit1.Show;
  Edit2.Show;
  DT1.Hide;
  DT2.Hide;
  Button1.Hide;
  Button4.Hide;
  Button2.Hide;
  Button7.Hide;
  Button8.Hide;
  Button9.Hide;
  Button10.Hide;
  Button11.Hide;
  Button14.Hide;
end;

function TForm1.connect(user:integer;password:integer):boolean;

begin
		result:=True;

      HcSound := nil;   // освобождаются ресрсы для переподключения
      HcFReg := nil;
      HcFRegFull := nil;
      HcReport := nil;
      HcFiscPrnt := nil;

    try
			conn:=TADOConnection.Create(self);
			with conn do
      begin
				CursorLocation:=clUseClient;
				LoginPrompt:=False;
				Provider:='EQL.EQL.1';
				//Если раскомментировать следующие две строки, то связь с кассой будет устанавливаться автоматически, не требуя от пользователя ввода дополнительной информации
				Properties['DBMS Name'].Value:='L2Com.HcComSessionCreator';
				//для упрощенного протокола источник данных задается в формате: номер_порта;0
				Properties['Data Source'].Value:='1;0';
//				Properties['Password'].Value:=inttostr(password);
//				Properties['User ID'].Value:=inttostr(user);
				//Если раскомментировать следующую строку, то окно с параметрами соединения будет появляться всегда
				//Properties['Prompt'].Value:=adPromptAlways;
				Open(inttostr(user),inttostr(password));
        Label1.Caption:='Кассир № '+IntToStr(user);
			end;

     lrst:=CoRecordset.Create;
     lrst.Open('EQL_service',conn.ConnectionObject,adOpenUnspecified,adLockUnspecified,adCmdTableDirect);
     Supports(lrst.Fields['Procedure'].Value,IHcSound,HcSound);
     Supports(lrst.Fields['Procedure'].Value,IHcFReg,HcFReg);
     Supports(lrst.Fields['Procedure'].Value,IHcFRegFull,HcFRegFull);
     Supports(lrst.Fields['Procedure'].Value,IHcReport,HcReport);
     Supports(lrst.Fields['Procedure'].Value,IHcFiscPrnt,HcFiscPrnt);

  Edit1.Hide;
  Edit2.Hide;
  Label3.Hide;
  Label4.Hide;
  Button1.Show;
  Button4.Show;
  Button7.Show;
  Button8.Show;
  Button14.Show;
  Button11.Show;
  Button2.Show;
  DT1.Show;
  DT2.Show;
  if (Label1.Caption='Кассир № 0') or (Label1.Caption='Кассир № 14')  then else
  begin
    HcFReg.BegChk;
    HcFReg.VoidChk;
  end;
  except   // оБРАБотка ошибок при подлючении
    on E:EOleException do
    begin
    if E.ErrorCode = -2147220991 then
    begin
      LogText('(E) Не найден кассовый аппарат!' + E.Message);
      MessageBox(Handle,' Не найден кассовый аппарат! ', 'Выход', MB_OK);
      conn.Close;
      conn.Free;
      Exit;
    end else
    if E.ErrorCode = -2147220174 then
    begin
      LogText('(E) !' + E.Message);
      MessageBox(Handle,' Не правильный пароль или имя кассира! ', 'Выход', MB_OK);
      conn.Close;
      conn.Free;
      Exit;
    end else
    if E.ErrorCode = -2147219458 then
    begin
      LogText('(E) !' + E.Message);
      MessageBox(Handle,' Последний чек отменен из-за ошибки! ', 'Выход', MB_OK);
      rfDoClose;
      Exit;
    end else
    if E.ErrorCode = -2147219501 then
    begin
      LogText('(E) !' + E.Message);
      MessageBox(Handle,' Смена слишком затянулась. Нужно сделать дневной Z-отчет с обнулением!! ', 'Выход', MB_OK);
    end
    else
    if E.ErrorCode = -2147219463 then
    begin
      try
          HcFReg.SmenBegin;
          LogText('(X)Произошла смена кассира');
          MessageBox(Handle,' Произошла смена кассира! ', 'Выход', MB_OK);
          HcSound.OutTone('200','1500');
      except
          on E:EOleException do
          if E.ErrorCode = -2147219501 then
          begin
            LogText('(E) !' + E.Message);
            MessageBox(Handle,' Смена слишком затянулась. Нужно сделать дневной Z-отчет с обнулением!! ', 'Выход', MB_OK);
          end
          else
          begin
            LogText('(E) !' + E.Message);
            MessageBox(Handle,PChar(' Непредвиденная ошибка! '+ Format('Код:%d', [E.Errorcode])), 'Выход', MB_OK);
          end;
      end;
    end  else
    if E.ErrorCode = -2147024809 then
    begin
          LogText('(E) !' + E.Message);
          MessageBox(Handle,'Логический номер не зарегистрирован или кассовый аппарат занят другой программой! ', 'Выход', MB_OK);
          Exit;
    end  else
      begin
      LogText('(E) !' + E.Message);
      MessageBox(Handle,PChar(' Непредвиденная ошибка! '+ Format('Код:%d', [E.Errorcode])), 'Выход', MB_OK);
      Application.Terminate;
      end;
    end;
 end;
 HcSound.OutTone('200','2000');
end;




procedure TForm1.Edit5KeyPress(Sender: TObject; var Key: Char);
begin   // фильтр при нажатии для ввода только числа
     if not (Key in ['0'..'9', ',', '-', #8])then Key:=#0;
end;

procedure TForm1.Button10Click(Sender: TObject);
begin
 Timer1.Enabled:=False;
 Panel4.Color:=clRed;
 JvTrayIcon1.Icon := Image2.Picture.Icon;
 Panel4.Caption:='Стоп';
  unreg;
  connect(14,555555);
     rfReport(repGoods, repZ);

     unreg;
     connect(StrToInt(Edit1.Text),StrToInt(Edit2.Text));

 Timer1.Enabled:=True;

end;

procedure TForm1.Button11Click(Sender: TObject);
 var
 adm : Trst;
begin
 Timer1.Enabled:=False;
 Panel4.Color:=clRed;
 JvTrayIcon1.Icon := Image2.Picture.Icon;
 Panel4.Caption:='Стоп';

  Form1.Button3Click(Sender);
  if Label5.Caption = '0' then
  begin
    unreg;
    connect(0,751426);
    adm:=CoRecordset.Create;
    adm.Open('Adm',conn.ConnectionObject,adOpenDynamic,adLockBatchOptimistic,adCmdTable);;
    Label1.Caption := DateToStr(Now)+' '+TimeToStr(Now);
    adm.Fields['CurTim'].Value := Label1.Caption;
    adm.UpdateBatch(adAffectCurrent);
    unreg;
    connect(StrToInt(Edit1.Text),StrToInt(Edit2.Text));
  end else
    MessageBox(Handle,' Аппарат не обнулен! Время можно установить только после дневного Z-отчета.', 'Выход', MB_OK) ;
    Timer1.Enabled:=True;
end;

procedure TForm1.Button12Click(Sender: TObject);
begin
     SetParams;
end;

procedure TForm1.Button13Click(Sender: TObject);
begin
  if (Edit1.Text = '') or (Edit2.Text = '') then
    MessageBox(Handle,' Пустой номер кассира или пароль! Введите номер кассира! ', 'Выход', MB_OK)
  else
  begin
    if Edit1.Visible=true then if Label1.Caption = 'Кассир не зарегистрирован' then else unreg;
    if Label1.Caption = 'Кассир не зарегистрирован' then
    begin
     LogText('(%)АВТОНОМНЫЙ РЕЖИМ ВКЛЮЧЁН');
     LogText(' . rfLogIn(Num='+Edit1.Text+',Psw="'+Edit2.Text+'")');
     if connect(StrToInt(Edit1.Text),StrToInt(Edit2.Text)) then  else
        begin
          LogText('(E) Не могу соединится с кассовым аппаратом! ');
          MessageBox(Handle,' Не могу соединится с кассовым аппаратом!', 'Выход', MB_OK);
          Exit;
        end;
     prFolders(Edit3.Text, Edit3.Text + 'ARCHIVE\');
    end;
  end;
  if Label1.Caption = 'Кассир не зарегистрирован' then
  else
  begin
    Timer1.Enabled := True;
    Button9.Hide;
    Button10.Hide;
    startproc := 0; 
    Self.Hide;
  end;
end;


procedure TForm1.Button14Click(Sender: TObject);
begin
    Edit1.Show;
    Edit2.Show;
    Label3.Show;
    Label4.Show;
    LogText('(X)АВТОНОМНЫЙ РЕЖИМ ВЫКЛЮЧЁН');
    Timer1.Enabled := False;
    Panel4.Color:=clSilver;
    JvTrayIcon1.Icon := Image3.Picture.Icon;
    Panel4.Caption:='Сост';
    startproc := 1;
    unreg;
    Button14.Hide;
end;

procedure TForm1.Button15Click(Sender: TObject);
begin
     rfDoClose;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  Form1.Button3Click(Sender);
  if Label5.Caption = '0' then
    MessageBox(Handle,' Аппарат уже обнулен!', 'Выход', MB_OK)
  else
  begin
    Timer1.Enabled := False;
    Button9.Show;
    Button10.Show;
  end;

end;

procedure TForm1.Button2Click(Sender: TObject);
begin
    unreg;
    connect(14,555555) ;
    rfOtchet(DateToStr(DT1.Date),DateToStr(DT2.Date));
    unreg;
    connect(StrToInt(Edit1.Text),StrToInt(Edit2.Text));
end;

procedure TForm1.Button3Click(Sender: TObject);
var
  LentaF: TextFile;
	arst:TRst;
  ocek, orasp, oout, oin, cek, rasp, sout, sin: integer ;
  nameTov : Array of string;
  summaTov : Array of real;
  kolTov : Array of integer;
  myy, number : Integer;
  osumma, summa, summa_card, osumin, sumin, osumout, sumout, zsumma, allsum, tmpsumm: Real;
begin
  AssignFile(LentaF, 'Lenta.txt');
  ocek:=0; orasp:=0; oout:=0; oin:=0; cek:=0; rasp:=0; sout:=0; sin:=0; tmpsumm:=0;
  osumma:=0; summa:=0; osumin:=0; sumin:=0; osumout:=0; sumout:=0; zsumma:=0; summa_card := 0;
  if conn.Connected = false  then
  begin
    MessageBox(Handle,'Для чтения ленты нужно создать соединенние', 'Создайте соединение', MB_OK);
		Exit;
	end;
  Timer1.Enabled:=false;
  Panel4.Color:=clRed;
  JvTrayIcon1.Icon := Image2.Picture.Icon;
  Panel4.Caption:='Стоп';
	arst:=CoRecordset.Create;
	arst.Open('Check',conn.ConnectionObject,adOpenDynamic, adLockReadOnly, adCmdTable);
  m1.Lines.Clear;
	try
    Rewrite(LentaF);
    number := 0;
    SetLength(nameTov,1);
    SetLength(SummaTov,1);
    SetLength(kolTov,1);
    Writeln(LentaF,'Журнал сформовано ' + DateToStr(Now) + ' в ' + TimeToStr(Now));
		while not arst.EOF do begin
      number :=  number + 1;
      case arst.Fields['Info.Sel'].Value of
        $1E: if arst.Fields[0].Value = 0 then else
            begin
              Writeln(LentaF,'--------------------------------------------------') ;
              Writeln(LentaF,'Оператор ' + String(arst.Fields[31].Value) + ' почав зміну ' + TimeToStr(arst.Fields[32].Value));
              Writeln(LentaF,'--------------------------------------------------') ;
              if ocek = 0 then else
              begin
                m1.Lines.Add( 'Напечатано: ' + IntToStr(ocek) + ' чеков,');
                m1.Lines.Add( 'из них '+ IntToStr(orasp) + ' продаж,');
                m1.Lines.Add('сумма '+ Format('%f грн,',[osumma]));
                m1.Lines.Add( IntToStr(oin) + ' служебных внесений,');
                m1.Lines.Add('на сумму '+ Format('%f грн,',[osumin]));
                m1.Lines.Add( IntToStr(oout) + ' служебных изъятий,');
                m1.Lines.Add('на сумму '+ Format('%f грн,',[osumout]));
              end;
              m1.Lines.Add( '--------------------------------');
              m1.Lines.Add( ' Кассир № ' + String(arst.Fields[31].Value));
              ocek:=0; orasp:=0; osumma:=0; osumin:=0; oin:=0; oout:=0; osumout:=0;
            end;
        $32: begin
              Writeln(LentaF,'----Z-звіт по товарам ' + TimeToStr(arst.Fields[14].Value) + '-----') ;
              for myy := 1 to Length(kolTov)-1 do
              begin
                if kolTov[myy] > 0 then
                Writeln(LentaF, nameTov[myy] + Format(':  %d, на суму ',[kolTov[myy]]) + Format('%f грн',[summaTov[myy]]));
                kolTov[myy] := 0 ;
                SummaTov[myy] := 0;
              end;
              Writeln(LentaF, 'Загальнна сума продаж: ' + Format('%f грн',[zsumma]));
              Writeln(LentaF,'---------------Зміну закінчено.----------------');
              zsumma := 0;
             end;

        $14:  if arst.Fields[0].Value = 0 then
              Writeln(LentaF,'ВИДАЛЕНО Службове внесення ' + String(arst.Fields[71].Value) + ' грн')
            else
            begin
              tmpsumm := arst.Fields[71].Value;
              if tmpsumm > 0 then
              begin
                Writeln(LentaF,'Службове внесення ' + String(arst.Fields[71].Value) + ' грн');
                sin:=sin+1;
                oin:=oin+1;
                osumin:=osumin + tmpsumm;
                sumin:=sumin + tmpsumm;
              end else
              begin
                Writeln(LentaF,'Службова видача ' + String(arst.Fields[71].Value) + ' грн');
                sout:=sout+1;
                oout:=oout+1;
                osumout:=osumout + tmpsumm;
                sumout:=sumout + tmpsumm;
              end;
            end;
        $2C: begin
              myy := arst.Fields[57].Value[0] + 256 * arst.Fields[57].Value[1];
             Writeln(LentaF, nameTov[myy]);
            if arst.Fields[0].Value = 0 then
            begin
              Writeln(LentaF,'ВИДАЛЕНО Фіскальний чек на ' + String(arst.Fields[59].Value) + ' грн');
              Writeln(LentaF,'--------------------------------------------------');
            end
            else
            begin
              tmpsumm := arst.Fields[59].Value ;
              Writeln(LentaF,'Фіскальний чек на ' + FloatToStr(tmpsumm) + ' грн');
              orasp:=orasp+1;
              rasp:=rasp+1;
              kolTov[myy]:= kolTov[myy] + 1;
              summaTov[myy]:= summaTov[myy] + tmpsumm;
              summa := summa +  tmpsumm;
              osumma := osumma + tmpsumm;
              zsumma := zsumma + tmpsumm;
            end;
          end;
        $1D:  if arst.Fields[0].Value = 0 then
            Writeln(LentaF,'ВИДАЛЕНО Чек надруковано ' + TimeToStr(arst.Fields[42].Value))
            else
            begin
              Writeln(LentaF) ;
              Writeln(LentaF,'Чек надруковано ' + TimeToStr(arst.Fields[42].Value));
              Writeln(LentaF,'**************Аванси: ' + Format('%f грн,',[sumin+sumout]));
              Writeln(LentaF,'**************Продаж: ' + Format('%f грн,',[summa]));
              Writeln(LentaF,'--------------------------------------------------');
              cek:=cek+1;
              ocek:=ocek+1;
            end;
        $1C:  if arst.Fields[0].Value = 0 then else
                Write(LentaF,String(arst.Fields[63].Value));
        $13:  if arst.Fields[0].Value = 0 then else
                begin
                  tmpsumm := arst.Fields[68].Value ;
                  if tmpsumm > 0 then
                  begin
                    Writeln(LentaF);
                    if arst.Fields[67].Value = 4 then
                    Writeln(LentaF,'Картка ' + FloatToStr(tmpsumm) + ' грн')
                    else
                    Writeln(LentaF,'Готівка ' + FloatToStr(tmpsumm) + ' грн');
                  end else
                    Writeln(LentaF,'Здача ' + FloatToStr(tmpsumm) + ' грн') ;
                  if arst.Fields[67].Value = 4 then
                  begin

                    summa_card := summa_card + tmpsumm;
                  end;
                end;
        $60:  begin
                SetLength(nameTov, number+1);
                SetLength(summaTov, number+1);
                SetLength(kolTov, number+1);
                myy := number;
                nameTov[myy]:= String(arst.Fields[50].Value) + ' ';
              end;
        $61:  nameTov[myy]:= nameTov[myy] + String(arst.Fields[52].Value);
      end;
      arst.MoveNext;
		end;
                m1.Lines.Add( 'Напечатано: ' + IntToStr(ocek) + ' чеков,');
                m1.Lines.Add( 'из них '+ IntToStr(orasp) + ' продаж,');
                m1.Lines.Add('сумма '+ Format('%f грн,',[osumma]));
                m1.Lines.Add( IntToStr(oin) + ' служебных внесений,');
                m1.Lines.Add('на сумму '+ Format('%f грн,',[osumin]));
                m1.Lines.Add( IntToStr(oout) + ' служебных изъятий,');
                m1.Lines.Add('на сумму '+ Format('%f грн,',[osumout]));
                m1.Lines.Add( '-------- Итого по товарам --------');
                Writeln(LentaF,'--Усього товарів протягом зміни---------------') ;
                for myy := 1 to Length(kolTov) - 1 do
                begin
                  if kolTov[myy] > 0 then
                  begin
                     Writeln(LentaF, nameTov[myy] + Format(':  %d, на суму ',[kolTov[myy]]) + Format('%f грн',[summaTov[myy]]));
                     m1.Lines.Add(nameTov[myy] );
                     m1.Lines.Add(Format('    %d       ',[kolTov[myy]]) + Format(' на сумму %f грн,',[SummaTov[myy]]));
                  end;
                end;
                allsum := sumout+sumin+summa-summa_card;
                m1.Lines.Add( '-------- Итого на ' + TimeToStr(Now) + ' --------');
                m1.Lines.Add('Продаж за смену: '+ Format('%f грн,',[zsumma]));
                m1.Lines.Add('Продаж за день: '+ Format('%f грн,',[summa]));
                m1.Lines.Add('Продаж наличными: '+ Format('%f грн,',[summa-summa_card]));
                m1.Lines.Add('Сл. внесений: '+ Format('%f грн,',[sumin]));
                m1.Lines.Add('Сл. изъятий: '+ Format('%f грн,',[sumout]));
                m1.Lines.Add('Продаж карткой: '+ Format('%f грн,',[summa_card]));
                Label5.Caption:=IntToStr(cek);
	finally
    CloseFile(LentaF);
	end;
  arst.Close;
//  arst:=CoRecordset.Create;
//	arst.Open('FDay',conn.ConnectionObject,adOpenDynamic, adLockReadOnly, adCmdTable);
//  while not arst.EOF do begin
//    summa := summa + arst.Fields['STax1'].Value;
//    arst.MoveNext;
//  end;
//    arst.MoveLast;
//  arst.Close;
  m1.Lines.Add('Сумма в ящике: ' + FloatToStrF(allsum,ffCurrency,9,2));
  m1.Lines.Add('Аванс пользователей: ' + FloatToStrF(sumout+sumin-StrToFloat(Edit5.Text),ffCurrency,9,2));// - StrToFloat(Edit5.Text),ffCurrency,9,2));
//  m1.Lines.Add('Сумма в ФП: ' + FloatToStrF(summa,ffCurrency,9,2));
  Timer1.Enabled:=true;
end;


procedure TForm1.Button4Click(Sender: TObject);
begin
 HcFiscPrnt.OpenSafe;
end;

procedure TForm1.Button5Click(Sender: TObject);
var SumF: TextFile;
    ssum: String;
begin
   AssignFile(SumF, 'Summa.ini');
      if slughb = 0 then if MessageDlg('Вы действительно хотите изменить сумму на начало дня?!',mtError, mbOKCancel, 0) = mrOK then
      begin
       try
        Rewrite(SumF);
        Writeln(SumF, Edit5.text);
       finally
        CloseFile(SumF);
       end;
      end else
      begin
        try
          Reset(SumF);
          Readln(SumF,ssum);
          Edit5.Text := ssum;
        finally
          CloseFile(SumF);
        end;
      end else
      begin
       try
        Rewrite(SumF);
        Writeln(SumF, Edit5.text);
       finally
        CloseFile(SumF);
       end;
      end;


end;


procedure TForm1.Button7Click(Sender: TObject);
begin
 Timer1.Enabled:=False;
 Panel4.Color:=clRed;
 JvTrayIcon1.Icon := Image2.Picture.Icon;
 Panel4.Caption:='Стоп';
     unreg;
     connect(14,555555);
     rfReport(repDaily, repX);
     unreg;
     connect(StrToInt(Edit1.Text),StrToInt(Edit2.Text));
 Timer1.Enabled:=True;
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
 Timer1.Enabled:=False;
 Panel4.Color:=clRed;
 JvTrayIcon1.Icon := Image2.Picture.Icon;
 Panel4.Caption:='Стоп';
     unreg;
     connect(14,555555);
     rfReport(repGoods, repX);
     unreg;
     connect(StrToInt(Edit1.Text),StrToInt(Edit2.Text));
 Timer1.Enabled:=True;
end;

procedure TForm1.Button9Click(Sender: TObject);
var FileName : String;
    index : Integer;
begin
 Timer1.Enabled:=False;
 Panel4.Color:=clRed;
 JvTrayIcon1.Icon := Image2.Picture.Icon;
 Panel4.Caption:='Стоп';
     Button9.Hide;
     Button10.Hide;
     if MessageDlg('Вы действительно хотите обнулить кассовый аппарат?!',mtError, mbOKCancel, 0) = mrOK then
     begin
     FileName := LentaFolder + FormatDateTime('yyyy.mm.dd', Now);
     index := 0;
     while FileExists(FileName + '.txt') do
     begin
        FileName := LentaFolder + FormatDateTime('yyyy.mm.dd', Now);
        index := index + 1;
        FileName := FileName + '_' + IntToStr(index);
     end;

      CopyFile(PChar('Lenta.txt'),PChar(FileName + '.txt'),false) ;
      unreg;
      connect(14,555555);
      rfReport(repDaily, repZ);
      slughb := 1;
      Edit5.Text := '0';
      Form1.Button5Click(Sender);
      slughb := 0;
      unreg;
//      connect(StrToInt(Edit1.Text),StrToInt(Edit2.Text));
     end;
// Timer1.Enabled:=True;
end;


procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
     if MessageDlg('Вы действительно хотите выйти из приложения?!',mtError, mbOKCancel, 0) = mrOK then
     begin
     Application.Terminate;
     WinExec(PANsiChar('TASKKILL /F /IM Rf2160.exe'), SW_HIDE);
     end else
     begin
     Action:=caNone;
     Self.Hide;
     end;
end;

procedure TForm1.FormCloseQuery(Sender: TObject; var CanClose: Boolean);
begin
   Application.CancelHint;
end;

procedure TForm1.FormCreate(Sender: TObject);

var k : Integer;
    SumF : TextFile;
    Ssum : String;
begin


MyMutex := CreateMutex(nil,false,'MyKassa');
k := GetLastError();
if (k=ERROR_ALREADY_EXISTS)or(k=ERROR_ACCESS_DENIED) then
begin
 MessageBox(Handle,' Приложение уже запущено!', 'Выход', MB_OK)  ;
 Application.Terminate;
 Exit;
end;
     SetParams;
     FileList := TStringList.Create;
     CurrFile := TStringList.Create;
     Init();
     DT1.DateTime:=Now-30;
     DT2.DateTime:=Now;
     AssignFile(SumF, 'Summa.ini') ;
    try
     Reset(SumF);
     Readln(SumF,ssum);
     Edit5.Text := ssum;
    finally
     CloseFile(SumF);
    end;
end;

procedure TForm1.FormDestroy(Sender: TObject);
begin
      Application.Terminate;;
end;

procedure TForm1.JvTrayIcon1DblClick(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
     Self.Show;
end;

procedure TForm1.SetParams;
begin
     WorkFolder := Edit3.Text;
     if not DirectoryExists(WorkFolder) then
          MkDir(WorkFolder);
     MoveFolder := Edit3.Text + 'ARCHIVE\';
     if not DirectoryExists(MoveFolder) then
          MkDir(MoveFolder);
     LentaFolder := Edit4.Text;
     if not DirectoryExists(LentaFolder) then
          MkDir(LentaFolder);
     Psw := Edit2.Text;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
 Timer1.Enabled:=False;
 Panel4.Color:=clRed;
 JvTrayIcon1.Icon := Image2.Picture.Icon;
 Panel4.Caption:='Стоп';
 try
       if startproc = 0 then
       begin
          slughb := 0;
          startproc := 1;
          ProcessFiles;
          if slughb <> 0 then
          begin
            slughb := slughb + StrToFloat(Edit5.Text);
            Edit5.Text := FloatToStrF(slughb,ffFixed,9,2);
            Form1.Button5Click(Sender);
            slughb := 0;
          end;
       end;
  except
  on E:EOleException do
  begin
    if E.ErrorCode = -2147219516 then
    begin
          LogText('(X)Имя изменено, отмена чека');
          MessageBox(Handle,' Изменено название товара!  Чек отменен! Сделайте Z-отчет или верните старое название', 'Выход', MB_OK);
          HcFReg.VoidChk;
          HcSound.OutTone('200','1500');
          Self.Show;
          Exit;
    end  else
    if E.ErrorCode = -2147219469 then
    begin
      LogText('(E) !' + E.Message);
      MessageBox(Handle,' Нехватает денег в кассе для выдачи! Чек отменен ', 'Выход', MB_OK);
      HcFReg.VoidChk;
      Self.Show;
      Exit;
    end else
    if (E.ErrorCode = -2147219487) or (E.ErrorCode = -2147219711) then
    begin
      LogText('(E) !' + E.Message);
      MessageBox(Handle,' В чеке нулевая сумма оплаты! Чек отменен ', 'Выход', MB_OK);
      HcFReg.VoidChk;
      Self.Show;
      Exit;
    end else
    if E.ErrorCode = -2147219458 then
    begin
      LogText('(E) Последний чек отменен из-за ошибки!');
      MessageBox(Handle,' Последний чек отменен из-за ошибки! ', 'Выход', MB_OK);
      rfDoClose;
      Self.Show;
      Exit;
    end else
    if E.ErrorCode = -2147219463 then
    begin
      LogText('(E) Исчезла регистрация кассира! Возможно пропадало питание кассового аппарата');
      MessageBox(Handle,' Исчезла регистрация кассира! Возможно пропадало питание кассового аппарата. Чек не напечатан!', 'Выход', MB_OK);
//      rfDoClose;
      Form1.Button14Click(Sender);
      Self.Show;
      Exit;
    end else
    begin
      LogText('(E) Непредвиденная ошибка! Чек отменен! ' + E.Message);
      MessageBox(Handle,PChar(' Непредвиденная ошибка! Чек отменен'+ Format('Код:%d', [E.Errorcode])), 'Выход', MB_OK);
      HcFReg.VoidChk;
      Self.Show;
      Exit;
    end;
  end;
  on E: Exception do
  begin
    if E.Message = 'I/O error 32' then
    Begin
    LogText('(E)' + E.Message);
    MessageBox(Handle,' Файл чека занят! Если ошибка повторяется, завершите программу и запустите снова!', 'Выход', MB_OK);
    Exit;
    end else
    begin
    LogText('(E)' + E.Message);
    Application.MessageBox(PAnsiChar(E.Message), 'Фатальная ошибка', MB_ICONERROR);
    Application.Terminate;
    Halt;
    end;
  end;
 end;
 if startproc = 0 then
 begin
    Panel4.Caption:='Раб';
    JvTrayIcon1.Icon := Image1.Picture.Icon;
    Panel4.Color:=clGreen;
 end;
 Timer1.Enabled:=True;
end;

end.
