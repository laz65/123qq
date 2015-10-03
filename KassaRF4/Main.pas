unit Main;

interface

uses
	Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
	StdCtrls, ADODB, ExtCtrls;

type
	TConn=TADOConnection;

type
	TFormMain = class(TForm)
		Button1: TButton;
		Button2: TButton;
		ScrollBox1: TScrollBox;
		Panel1: TPanel;
		m1: TMemo;
		Button3: TButton;
		Button4: TButton;
		Button5: TButton;
		procedure Button1Click(Sender: TObject);
		procedure Button2Click(Sender: TObject);
		procedure Button3Click(Sender: TObject);
		procedure Button5Click(Sender: TObject);
		procedure Button4Click(Sender: TObject);
		procedure FormCreate(Sender: TObject);
	private
		LogNum,User,Password:longint;
		conn:TConn;
		function connect: boolean;
		{ Private declarations }
	public
		{ Public declarations }
	end;

var
	FormMain: TFormMain;

implementation

uses ConnectionParams, NewItem, HcTLB_TLB, ItfProc, comobj, oledb, adoint;

{$R *.DFM}

type
	TRst=_Recordset;

function Omitted:OleVariant;
begin
	TVarData(result).VType:=varError;
	TVarData(result).VError:=LongWord(DISP_E_PARAMNOTFOUND);
end;

function TFormMain.connect:boolean;
var
	frm:TFormConnectionParams;
begin
	if True then begin //новый вариант: используется окно параметров соединения из провайдера
		result:=True;
		try
			conn:=TADOConnection.Create(self);
			with conn do begin
				CursorLocation:=clUseClient;
				LoginPrompt:=False;
				Provider:='EQL.EQL.1';
				//Если раскомментировать следующие две строки, то связь с кассой будет устанавливаться автоматически, не требуя от пользователя ввода дополнительной информации
				//Properties['DBMS Name'].Value:='L2Com.HcComSessionCreator';
				//для упрощенного протокола источник данных задается в формате: номер_порта;0
				//Properties['Data Source'].Value:='1;0';
				Properties['Password'].Value:=inttostr(Password);
				Properties['User ID'].Value:=inttostr(User);
				//Если раскомментировать следующую строку, то окно с параметрами соединения будет появляться всегда
				//Properties['Prompt'].Value:=adPromptAlways;
				Open;
			end;
		except
			on E:EOleException do begin
				if E.ErrorCode=DB_E_CANCELED then
					result:=False
				else raise;
			end;
			else
				raise;
		end;
	end
	else begin //старый вариант: только полный протокол
		//получаем параметры соединения
		frm:=TFormConnectionParams.Create(self);
		result:=True;
		try
	//		LogNum:=0;		User:=0;		Password:=0;
			frm.ELogNum.Text:=inttostr(LogNum);
			frm.EUser.Text:=inttostr(User);
			frm.EPassword.Text:=inttostr(Password);
			if frm.ShowModal=mrOk then begin
				try
					LogNum:=strtoint(frm.ELogNum.Text);
				except
				end;
				try
					User:=strtoint(frm.EUser.Text);
				except
				end;
				//Password:=strtoint(frm.EPassword.Text);
				//соединяемся
				conn:=TADOConnection.Create(self);
				with conn do begin
					CursorLocation:=clUseClient;
					LoginPrompt:=False;
					Provider:='EQL.EQL.1';
					Properties['Password'].Value:=frm.EPassword.Text;
					Properties['User ID'].Value:=frm.EUser.Text;
					Properties['Data Source'].Value:=frm.ELogNum.Text;
					Open;
				end;
			end
			else begin
				result:=false;
			end;
		finally
			frm.Close;
			frm.Release;
		end;
	end;
end;

procedure TFormMain.Button1Click(Sender: TObject);
begin
	if connect then begin
		Button2.Enabled:=True;
		Button3.Enabled:=True;
		Button4.Enabled:=True;
		Button5.Enabled:=True;
	end
	else begin
		Button2.Enabled:=False;
		Button3.Enabled:=False;
		Button4.Enabled:=False;
		Button5.Enabled:=False;
	end;
end;

function txtCheckLine(f:Field):PChar;
var
	id:Integer;
begin
	id:=f.Value;
	case id of
		$00:result:='Bad: Удаленная запись';
		$10:result:='Void: Диапазон отмены';
		$11:result:='Qty: Количество проданного товара';
		$13:result:='Rasp: Расплата';
		$14:result:='InOut: Внос/вынос';
		$15:result:='Prom: Промежуточный итог';
		$1C:result:='Comm: Комментарий';
		$1D:result:='Check: Конец чека';
		$1E:result:='Smen: Начало смены';
		$1F:result:='ZRep: Обнуляющий отчет';
		$2C:result:='Prod: Продажа';
		$2D:result:='Nac: Скидка/наценка';
		$31:result:='ZDep: ';
		$32:result:='ZTov: ';
		$33:result:='ZOpr: ';
		$34:result:='ZTim: ';
		$35:result:='ZLnt: ';
		$36:result:='RepFsk: ';
		$51:result:='PayOff: Выплата';
		$60:result:='Code: Код товара';
		$61:result:='Name: Имя товара';
		$cc:result:='NoFsChk: Не фискальный чек';
		$ee:result:='Offset: Лента просквизирована';
		$ff:result:='Empty: Пустая запись';
	else
		result:='UNKNOWN RECORD ID';
	end;
end;

procedure TFormMain.Button2Click(Sender: TObject);
var
	arst:TRst;
begin
	if not assigned(conn) then
		connect;
	if not assigned(conn) then  begin
		ShowMessage('Для чтения ленты нужно создать соединенние');
		Exit;
	end;
	arst:=CoRecordset.Create;
	arst.Open('Check',conn.ConnectionObject,adOpenDynamic, adLockReadOnly, adCmdTable);
	try
		while not arst.EOF do begin
			m1.Lines.Add(txtCheckLine(arst.Fields['Info.Sel']));
			arst.MoveNext;
		end;
	except
	end;
end;

function DelSpaces(s:String):String;
var
	i,z:integer;
begin
	z:=length(s);
	result:='';
	if z>0 then begin
		for i:=1 to z do begin
			if s[i]<>' ' then
				result:=result+s[i];
		end;
	end;
end;

function KillPoint(s:String):String;
begin
	if(length(s)>0)then begin
		if (s[1]='.') and (s[length(s)]='.') then begin
			result:='';
			Exit;
		end;
		if s[1]='.' then begin
			result:='0'+s;
			Exit;
		end;
		if s[length(s)]='.' then begin
			result:=s+'0';
			Exit;
		end;
	end;
	result:=s;
end;

procedure TFormMain.Button3Click(Sender: TObject);
var
	frm:TNewPLU;
	plu:TRst;
	Criteria:WideString;
	Code,aName,Cen,Dep,Grp,Tax,Kol,Flg:String;
begin
	frm:=TNewPLU.Create(self);
	try
		//вставить начальные значения
		//вызвать диалог
		if frm.ShowModal=mrOk then begin
			//проанализировать введенные  значения
			with frm do begin
				Code:=DelSpaces(ECode.Text);
				aName:=EName.Text;
				Cen:=KillPoint(DelSpaces(EPrice.Text));
				Dep:=DelSpaces(EDep.Text);
				Grp:=DelSpaces(EGrp.Text);
				Tax:=DelSpaces(ETax.Text);
				Kol:=KillPoint(DelSpaces(EQty.Text));
				Flg:=DelSpaces(EFlg.Text);
			end;
			//открыть таблицу товаров
			plu:=CoRecordset.Create;
			plu.Open('PLU',conn.ConnectionObject,adOpenDynamic,adLockBatchOptimistic,adCmdTable);
			//поискать указанный товар
			plu.MoveFirst;
			Criteria:='Code = '+Code;
			plu.Find(Criteria,0,adSearchForward,Omitted);
			//если такого товара нет, то вставить его
			if plu.EOF then begin
				plu.AddNew(Omitted,Omitted);
				plu.Fields['Code'].Value:=Code;
				plu.Fields['Name'].Value:=aName;
				if length(Cen)=0 then Cen:='0.0';
				plu.Fields['Cen'].Value:=Cen;
				if length(Dep)=0 then Dep:='0';
				plu.Fields['Dep'].Value:=Dep;
				if length(Grp)=0 then Grp:='0';
				plu.Fields['Grp'].Value:=Grp;
				if length(Tax)=0 then Tax:='0';
				plu.Fields['Tax'].Value:=Tax;
				if length(Kol)=0 then Kol:='0.0';
				plu.Fields['Kol'].Value:=Kol;
				if length(Flg)=0 then Flg:='1';
				plu.Fields['Flg'].Value:=Flg;
				//Сохранить внесенные изменения
				plu.UpdateBatch(adAffectAll);
			end
			//если такой товар есть, то модифицировать таблицу товаров
			else begin
				if length(aName)>0 then
					plu.Fields['Name'].Value:=aName;
				if length(Cen)>0 then
					plu.Fields['Cen'].Value:=Cen;
				if length(Dep)>0 then
					plu.Fields['Dep'].Value:=Dep;
				if length(Grp)>0 then
					plu.Fields['Grp'].Value:=Grp;
				if length(Tax)>0 then
					plu.Fields['Tax'].Value:=Tax;
				if length(Kol)>0 then
					plu.Fields['Kol'].Value:=Kol;
				if length(Flg)>0 then
					plu.Fields['Flg'].Value:=Flg;
				//Сохранить внесенные изменения
				plu.UpdateBatch(adAffectAll);
			end;
		end;
	finally
		frm.Close;
		frm.Release;
	end;
end;

{$IFDEF CONDITIONALEXPRESSIONS}
{$IF not Declared(CompilerVersion) or (CompilerVersion<14.0)}
{$DEFINE ADOVERCHECK}
{$IFEND}
{$ELSE}
{$DEFINE ADOVERCHECK}
{$ENDIF}

procedure TFormMain.Button5Click(Sender: TObject);
var
	lrst:TRst;
	igdi:IHcGetDriverInfo;
	procitf: Variant;//IDispatch;
	{$IFDEF ADOVERCHECK}
	ADOVer:Real;
	ErrCode:Integer;
	{$ENDIF}
begin
	lrst:=CoRecordset.Create;
	lrst.Open('EQL_service',conn.ConnectionObject,adOpenUnspecified,adLockUnspecified,adCmdTableDirect);
	m1.lines.add('Серийный номер: '+String(lrst.Fields['Letters'].Value)+String(lrst.Fields['Serial'].Value));
	procitf:=lrst.Fields['Procedure'].Value;
	{$IFDEF ADOVERCHECK}
	Val(conn.Version,ADOVer,ErrCode);
	if (ErrCode<>0) or (ADOVer<2.6) then begin
		IDispatch(TVarData(procitf).VDispatch)._Release;
		IDispatch(TVarData(procitf).VDispatch)._Release;
	end;
	{$ENDIF}
	if Supports(procitf,IHcGetDriverInfo,igdi)
	then m1.lines.add('Модель кассы: '+igdi.Name)
	else m1.lines.add('Модель кассы неизвестна');
end;

procedure TFormMain.Button4Click(Sender: TObject);
var
	frm:TProcItfForm;
	lrst:TRst;
	procitf: Variant;//IDispatch;
	{$IFDEF ADOVERCHECK}
	ADOVer:Real;
	ErrCode:Integer;
	{$ENDIF}
begin
	lrst:=CoRecordset.Create;
	lrst.Open('EQL_service',conn.ConnectionObject,adOpenUnspecified,adLockUnspecified,adCmdTableDirect);
	procitf:=lrst.Fields['Procedure'].Value;
	{$IFDEF ADOVERCHECK}
	Val(conn.Version,ADOVer,ErrCode);
	if (ErrCode<>0) or (ADOVer<2.6) then begin
		IDispatch(TVarData(procitf).VDispatch)._Release;
		IDispatch(TVarData(procitf).VDispatch)._Release;
	end;
	{$ENDIF}

	frm:=TProcItfForm.Create(self);
	try
		//вставить начальные значения
		frm.procitf:=procitf;
		frm.Init;
		//вызвать диалог
		if frm.ShowModal=mrOk then begin
		end;
	finally
		frm.Close;
		frm.Release;
	end;
end;

procedure TFormMain.FormCreate(Sender: TObject);
begin
	User:=1;
	Password:=0;
end;

end.
