unit rfUnit;

interface
uses SysUtils, Classes, HcTLB_TLB, Windows;

const
  Header: String[18] = 'FISREGISTRATOR2160';
  SOH	= #$01;
	STX = #$02;
	ETX	= #$03;
	EOT	= #$04;
	ENQ	= #$05;
	ACK	= #$06;
	FS	= #$1C;
	ETB	= #$17;
	NAK	= #$15;

  ofsLen = 21;
  ofsData = 24;

  mBit0 = 1;
  mBit1 = 2;
  mBit2 = 4;
  mBit3 = 8;
  mBit4 = 16;
  mBit5 = 32;
  mBit6 = 64;
  mBit7 = 128;

  rmOff = '0';
  rmWork = '1';
  rmXmode = '2';
  rmZmode = '3';
  rmPmode = '4';

  repX = 'X';
  repZ = 'Z';

  repDaily = #$E0;
  repCashier = #$E6;
  repGoods = #$E8;

  stdSize = 30;

  srvGet = '0';
  srvPut = '1';

  MaxStringSize = 1200;

  PauseTime = 250;
  MaxRetries = 3;

  txtPacket = '    ...  ';

type
  TRFPacket = record
      TotalLen,
      DataLen: Integer;
      Data: array [0..MaxStringSize] of Char;
  end;

var

  SndPacket,
  RcvPacket: TRFPacket;
  LogFile: TFileStream = nil;
  slughb : real;
  HcSound : IHcSound;
  HcFReg : IHcFReg;
  HcFRegFull : IHcFRegFull;
  HcReport : IHcReport;
  HcFiscPrnt : IHcFiscPrnt;
  LogFileName: String = 'rf.log';
  CallBackBusy: procedure = nil;
  CallBackDone: procedure = nil;
  WorkMode: Char = rmOff;
  STS1, STS2, STS3, STS4: Integer;

procedure Init();
procedure IntToFixed(Value: LongWord; PtrOfs: Integer; PtrLen: Integer = 8);
procedure LogText(AStr: String; LogDT: Boolean = True);
procedure LogCRLF;
procedure LogError(AErr: String);
procedure RaiseError(AErr: String);
procedure rfOpenRegister;
procedure rfResetRF;
procedure rfReport(repType: Char; repMode: Char);
procedure rfOtchet(repType: string; repMode: string);
procedure rfServicePay(payType: Char; ASum: String; ACom: String);
procedure rfProgramGoods(Code, Tid, Oid, Did, Gid, Gcd, Qty, Price: Integer; Name: String);
procedure rfComment(Comment: String);
procedure rfDoSale(Code, Qty: Integer);
procedure rfDoPay(Sum: Integer; Oid: string);
procedure rfDoClose;


implementation


procedure Init();
begin
     try
        LogFile := TFileStream.Create(LogFileName, fmOpenReadWrite or fmShareDenyNone);
        LogFile.Position := LogFile.Size;
     except
        try
           LogFile := TFileStream.Create(LogFileName, fmCreate);
        except
           raise Exception.Create('005: Не могу открыть файл протокола.');
        end;
     end;

    LogCRLF;
     LogCRLF;
    LogCRLF;
     LogText('***ЗАПУСК ПРОГРАММЫ');
     LogCRLF;
end;


procedure LogText(AStr: String; LogDT: Boolean);
var S: String;
begin
     S := AStr;
     if LogDT then S := S+'       ['+DateTimeToStr(Now)+']';
     LogFile.Write(S[1], Length(S));
     LogCRLF;
end;

procedure LogCRLF;
var S: String;
begin
     S := #13#10; // CRLF
     LogFile.Write(S[1], Length(S));
end;


procedure rfOpenRegister;
begin
     LogText(' . rfOpenRegister()');
end;

procedure rfResetRF;
begin
     LogText(' . rfResetRF()');
end;

procedure rfReport(repType: Char; repMode: Char);
var rep:String;
begin
  LogText(' . rfReport(repType='+repType+',repMode='+repMode+')');
 if  repMode = repZ then if repType = repDaily then Rep := '0';
 if  repMode = repZ then if repType = repGoods then Rep := '21';
 if  repMode = repX then if repType = repDaily then Rep := '10';
 if  repMode = repX then if repType = repGoods then Rep := '20';
 if  repMode = '0' then if repType = '0' then Rep := '1';
 HcReport.PrintReport(Rep);
end;

procedure rfOtchet(repType: string; repMode: string);
begin
     LogText(' . rfReport(repPeriod='+repType+',repMode='+repMode+')');
 HcFiscPrnt.FMReport(3,repType,repMode,0,0);
end;

procedure rfServicePay(payType: Char; ASum: string; ACom: string);
var
  sum:string;
  typ:integer;
  summa_temp : real;
begin
     LogText(' . rfServicePay(payType='+payType+',ASum='+ASum+')');
    summa_temp := StrToInt(ASum);
    summa_temp := summa_temp / 100;
    sum := FloatToStrF(summa_temp,ffFixed,9,2);
    if payType = '0' then sum := '-'+sum;
    if Acom = 'Службовий' then slughb := StrToFloat(sum);

  HcFReg.BegChk;
  HcFReg.InOut(0,sum);
  HcFReg.TextComment(ACom);
  HcFReg.EndChk;
  HcFiscPrnt.OpenSafe;

end;

procedure IntToFixed(Value: LongWord; PtrOfs: Integer; PtrLen: Integer);
var
    P, i: Integer;
    V: LongWord;
    B: Byte;
begin
     P := PtrOfs + (PtrLen-1);
     V := Value;
     for i := 0 to (PtrLen-1) do
     begin
          B := V and $FF;
          SndPacket.Data[P] :=  Chr(B);
          Dec(P);
          V := V shr 8;
     end;
end;


procedure rfProgramGoods(Code, Tid, Oid, Did, Gid, Gcd, Qty, Price: Integer; Name: String);
var typ: Integer;
  sum,pric:string;
  summa_temp : real;
begin
     LogText(' . rfProgramGoods(Code=' + IntToStr(Code) +
                               'TaxId=' + IntToStr(Tid) +
                               'OpId=' + IntToStr(Oid) +
                               'DivId=' + IntToStr(Did) +
                               'Qty=' + IntToStr(Qty) +
                               'Price=' + IntToStr(Price)
                               );
    summa_temp := Price;
    summa_temp := summa_temp / 100;
    sum := FloatToStrF(summa_temp,ffFixed,9,2);

 HcFReg.BegChk;
 HcFRegFull.FullProd(IntToStr(Code),sum,'1,000',IntToStr(Did),'1',IntToStr(Tid),name);
end;

procedure rfComment(Comment: String);
begin
 LogText(' . rfComment(Comment="'+Comment+'")');
 HcFReg.TextComment(Comment);
end;

procedure rfDoSale(Code, Qty: Integer);
begin
     LogText(' . rfDoSale(Code='+IntToStr(Code)+',Qty='+IntToStr(Qty)+')');
end;

procedure rfDoPay(Sum: Integer; Oid: String);
var typ:Integer;
    summa_temp: real;
     Asum,suma:string;
begin
     LogText(' . rfDoPay(Sum='+IntToStr(Sum)+')');
    summa_temp := Sum;
    summa_temp := summa_temp / 100;
    suma := FloatToStrF(summa_temp,ffFixed,9,2);
 HcFReg.Oplata(Oid,suma,'0');
 HcFReg.EndChk;
 HcFiscPrnt.OpenSafe;
end;

procedure rfDoClose;
begin
LogText(' . rfDoClose()');
HcFreg.VoidChk;
end;


procedure LogError(AErr: String);
begin
     LogText('!!!ERR: '+AErr);
end;

procedure RaiseError(AErr: String);
begin
     LogError(AErr);
     raise Exception.Create(AErr);
end;

end.
