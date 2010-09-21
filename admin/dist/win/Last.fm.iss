; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[CustomMessages]
Version=0.0.0.0


[Setup]
OutputBaseFilename=Last.fm-0.0.0.0
VersionInfoVersion=2.0.0
VersionInfoTextVersion=2.0.0
AppName=Last.fm
AppVerName=Last.fm {cm:Version}
VersionInfoDescription=Last.fm Installer
AppPublisher=Last.fm
AppPublisherURL=http://www.last.fm
AppSupportURL=http://www.last.fm
AppUpdatesURL=http://www.last.fm
AppCopyright=Copyright 2010 Last.fm Ltd. (C)
DefaultDirName={pf}\Last.fm
UsePreviousAppDir=yes
DefaultGroupName=Last.fm
OutputDir=.
AllowNoIcons=yes
Compression=lzma
SolidCompression=yes
DisableReadyPage=yes
DirExistsWarning=no
DisableFinishedPage=no
ShowLanguageDialog=yes
WizardImageFile=wizard.bmp
WizardSmallImageFile=wizard_small.bmp
SetupIconFile=installer.ico
WizardImageBackColor=$ffffff
WizardImageStretch=no
AppMutex=Lastfm-F396D8C8-9595-4f48-A319-48DCB827AD8F, Audioscrobbler-7BC5FBA0-A70A-406e-A50B-235D5AFE67FB

; This should stay the same across versions for the installer to treat it as the same program.
; It will then work to install however many updates and then run the uninstall script for
; the first version.
AppId=LastFM

[Components]
Name: Radio; Description: Last.fm Radio

[Languages]
; The first string is an internal code that we can set to whatever we feel like
Name: "en"; MessagesFile: "compiler:Default.isl"
;Name: "fr"; MessagesFile: "..\res\French-15-5.1.11.isl"
;Name: "it"; MessagesFile: "..\res\Italian-14-5.1.11.isl"
;Name: "de"; MessagesFile: "..\res\German-2-5.1.11.isl"
;Name: "es"; MessagesFile: "..\res\SpanishStd-5-5.1.11.isl"
;Name: "pt"; MessagesFile: "..\res\BrazilianPortuguese-16-5.1.11.isl"
;Name: "pl"; MessagesFile: "..\res\Polish-8-5.1.11.isl"
;Name: "ru"; MessagesFile: "..\res\Russian-19-5.1.11.isl"
;Name: "jp"; MessagesFile: "..\res\Japanese-5-5.1.11.isl"
;Name: "cn"; MessagesFile: "..\res\ChineseSimp-12-5.1.11.isl"
;Name: "tr"; MessagesFile: "..\res\Turkish-3-5.1.11.isl"
;Name: "sv"; MessagesFile: "..\res\Swedish-10-5.1.12.isl"


[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: checkedonce

; The OnlyBelowVersion flag disables this on Vista as an admin-run installer can't install a quick launch
; icon to the standard user's folder location. Sucks.
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0, 6;


[Files]
; Needed to kill helper
;Source: "..\bin\killer.exe"; DestDir: "{app}"; Flags: ignoreversion

; Main files
Source: "..\..\..\_bin\radio.exe"; DestDir: "{app}"; Components: Radio ; Flags: ignoreversion
Source: "..\..\..\_bin\audioscrobbler.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\_bin\iPodScrobbler.exe"; DestDir: "{app}"; Flags: ignoreversion

;libraries
Source: "..\..\..\_bin\lastfm.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\_bin\unicorn.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\_bin\listener.dll"; DestDir: "{app}"; Flags: ignoreversion
        
;Source: "\bin\Updater.exe"; DestDir: "{app}"; Flags: ignoreversion
;Source: "\bin\CrashReporter.exe"; DestDir: "{app}"; Flags: ignoreversion
;Source: "\bin\Cleaner.exe"; DestDir: "{app}"; Flags: ignoreversion
;Source: "\bin\LastFmTools1.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "\bin\LastFmFingerprint1.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "\bin\Moose1.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "\bin\breakpad.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "\bin\Microsoft.VC80.CRT\*"; DestDir: "{app}\Microsoft.VC80.CRT"; Flags: ignoreversion

; Qt binaries
Source: "c:\Qt\4.7.0-beta2\\bin\QtCore4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "c:\Qt\4.7.0-beta2\\bin\QtGui4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "c:\Qt\4.7.0-beta2\\bin\QtNetwork4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "c:\Qt\4.7.0-beta2\\bin\QtXml4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "c:\Qt\4.7.0-beta2\\bin\QtSql4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "c:\Qt\4.7.0-beta2\\bin\phonon4.dll"; DestDir: "{app}"; Components: Radio; Flags: ignoreversion
;image formats
Source: "c:\Qt\4.7.0-beta2\\plugins\imageformats\qjpeg4.dll"; DestDir: "{app}\plugins\imageformats"; Flags: ignoreversion
Source: "c:\Qt\4.7.0-beta2\\plugins\imageformats\qgif4.dll"; DestDir: "{app}\plugins\imageformats"; Flags: ignoreversion
Source: "c:\Qt\4.7.0-beta2\\plugins\imageformats\qmng4.dll"; DestDir: "{app}\plugins\imageformats"; Flags: ignoreversion
;phonon
Source: "c:\Qt\4.7.0-beta2\\plugins\phonon_backend\phonon_ds94.dll"; DestDir: "{app}\plugins\phonon_backend"; Components: Radio; Flags: ignoreversion

;The stylesheets
Source: "..\..\..\lib\unicorn\unicorn.css"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\app\audioscrobbler\audioscrobbler.css"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\..\app\radio\radio.css"; DestDir: "{app}"; Components: Radio; Flags: ignoreversion

;Third party dependancies
;Source: "..\bin\LastFM.exe.config"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\bin\libfftw3f-3.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\bin\zlibwapi.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\bin\VistaLib32.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\bin\VistaLib64.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\bin\srv_httpinput.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\bin\srv_rtaudioplayback.dll"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\bin\srv_madtranscode.dll"; DestDir: "{app}"; Flags: ignoreversion

;Some text files
;Source: "..\ChangeLog.txt"; DestDir: "{app}"; Flags: ignoreversion
;Source: "..\COPYING"; DestDir: "{app}"; Flags: ignoreversion

;Source: "..\bin\data\*"; DestDir: "{app}\data"; Flags: ignoreversion recursesubdirs


[Registry]
Root: HKLM; Subkey: "Software\Last.fm\Client"; ValueType: string; ValueName: "Version"; ValueData: "{cm:Version}"; Flags: uninsdeletekey
Root: HKLM; Subkey: "Software\Last.fm\Client"; ValueType: string; ValueName: "Path"; ValueData: "{app}\radio.exe"; Flags: uninsdeletekey

; Register last.fm protocol only if it isn't already
Root: HKCR; Subkey: "lastfm"; ValueType: string; ValueName: ""; ValueData: "URL:lastfm"; Flags: uninsdeletekey
Root: HKCR; Subkey: "lastfm"; ValueType: string; ValueName: "URL Protocol"; ValueData: ""; Flags: uninsdeletekey
Root: HKCR; Subkey: "lastfm\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\radio.exe"" ""%1"""; Flags: uninsdeletekey
Root: HKCR; Subkey: "lastfm"; ValueType: string; ValueName: "URL Protocol"; ValueData: ""; Flags: uninsdeletekey

; Register Last.fm in the control panel


; This is just for deleting keys at uninstall
Root: HKCU; Subkey: "Software\Last.fm"; Flags: dontcreatekey uninsdeletekeyifempty
Root: HKLM; Subkey: "Software\Last.fm"; Flags: dontcreatekey uninsdeletekeyifempty
Root: HKCU; Subkey: "Software\Last.fm\Client"; Flags: dontcreatekey uninsdeletekey
Root: HKLM; Subkey: "Software\Last.fm\Client"; Flags: dontcreatekey uninsdeletekey


[INI]
Filename: "{app}\LastFM.url"; Section: "InternetShortcut"; Key: "URL"; String: "http://www.last.fm"


[Icons]
Name: "{group}\Last.fm"; Filename: "{app}\LastFM.exe"
Name: "{group}\Go to www.last.fm"; Filename: "{app}\LastFM.url"
Name: "{group}\{cm:UninstallProgram,Last.fm}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\Last.fm"; Filename: "{app}\LastFM.exe"; Tasks: desktopicon

; The OnlyBelowVersion flag disables this on Vista as an admin-run installer can't install a quick launch
; icon to the standard user's folder location. Sucks.
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Last.fm"; Filename: "{app}\LastFM.exe"; OnlyBelowVersion: 0,6; Tasks: quicklaunchicon


[Run]
; Launch normally for pre-Vista versions
Filename: "{app}\LastFM.exe"; Description: "{cm:LaunchProgram,Last.fm}"; Flags: nowait postinstall; OnlyBelowVersion: 0,6

; For Vista, we have to go through the VistaLib to get the apps to launch non-elevated.
; Not launching helper here (app does it on startup) as it led to two instances being launched
; through the VistaLib DLL.
Filename: "RunDll32.exe"; Parameters: "{code:GetPathVistaDll},RunNonElevated {code:AddQuotes|{app}\LastFM.exe}"; Description: "{cm:LaunchProgram,Last.fm}"; Flags: nowait postinstall; MinVersion: 0,6


[InstallDelete]
; So that these files get replaced on Win98 with their renamed versions (see above)
Type: files; Name: "{app}ext_metadata.dll";
Type: files; Name: "{app}ext_search.dll";
Type: files; Name: "{app}ext_sidebar.dll";
Type: files; Name: "{app}ext_notifyskype.dll";

; Old shortcut that lived in user desktop
;Type: files; Name: "{userdesktop}\Last.fm.lnk"

; Old startup shortcut that lived in common startup (this is now managed by the app itself to allow user disabling)
;Type: files; Name: "{commonstartup}\Last.fm Helper.lnk"


; This is the LAST step of uninstallation
[UninstallDelete]
; Legacy
;Type: files; Name: "{app}\LastFM.url"
;Type: files; Name: "{app}\UpTemp.exe"
Type: dirifempty; Name: "{app}"

; TODO: why don't we attempt this also on Vista? What could go wrong?
Type: filesandordirs; Name: "{localappdata}\Last.fm\Client"; OnlyBelowVersion: 0,6
Type: dirifempty; Name: "{localappdata}\Last.fm"; OnlyBelowVersion: 0,6

; This should be possible to delete as we're waiting until all the plugin uninstallers have been run.
Type: files; Name: "{commonappdata}\Last.fm\Client\uninst.bat"
Type: files; Name: "{commonappdata}\Last.fm\Client\uninst2.bat"
Type: filesandordirs; Name: "{commonappdata}\Last.fm\Client"
Type: dirifempty; Name: "{commonappdata}\Last.fm"


; This is the FIRST step of uninstallation
[UninstallRun]
; Vista only: We need to do this to clean out any HKCU and {localappdata} locations for a potential standard user who used the application.
; But we can't! Because there is currently no way of making the installer wait for the Cleaner to finish which means we'll end up with
; broken uninstalls.
;Filename: "RunDll32.exe"; Parameters: "{code:GetPathVistaDll},RunNonElevated {code:AddQuotes|{app}\Cleaner.exe}"; Flags: waituntilterminated runhidden; MinVersion: 0,6


[Code]
// Global variables
var g_firstRun: Boolean;

procedure QuitHelper(install: Boolean);
var
  helperPath: String;
  killerPath: String;
  processExitCode: Integer;
  execOK: Boolean;
begin

  // Since we ditched the helper altogether, we can only do the
  // brute force shutdown via killer.exe. Using the --quit method
  // will fail because the old helper exe will be incompatible with
  // the new moose.dll.
  if install then
  begin
    //MsgBox('install, extract temporary', mbInformation, MB_OK);
    ExtractTemporaryFile('killer.exe');
    killerPath := ExpandConstant('{tmp}\killer.exe');
  end
  else
  begin
    //MsgBox('uninstall, use killer from app', mbInformation, MB_OK);
    killerPath := ExpandConstant('{app}\killer.exe');
  end;

  execOK := Exec(killerPath, 'LastFMHelper.exe', '', SW_HIDE, ewWaitUntilTerminated, processExitCode);
  if (execOK = False) then MsgBox('Failed to shut down helper process', mbError, MB_OK);

end;

// This must be called before the install and its value stored
function IsUpgrade(): Boolean;
var
  sPrevPath: String;
begin
  sPrevPath := '';
  if not RegQueryStringValue(HKLM, 'Software\Microsoft\Windows\CurrentVersion\Uninstall\LastFM_is1', 'UninstallString', sPrevpath) then
    RegQueryStringValue(HKCU, 'Software\Microsoft\Windows\CurrentVersion\Uninstall\LastFM_is1', 'UninstallString', sPrevpath);
  Result := (sPrevPath <> '');
end;

function InitializeSetup(): Boolean;
begin
  QuitHelper(True);

  // Need to evaluate and store this before any installation has been done
  g_firstRun := not IsUpgrade();

  // Run setup
  Result := TRUE;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  if PageID = 14 then
  begin

    // We skip the final screen if it's first run and go straight into config wizard
    if g_firstRun then
      Result := TRUE
    else
      Result := FALSE;

  end;
end;

function GetPathVistaDll(Param: String): String;
var
  path: String;
begin
  if IsWin64() then
    path := AddQuotes( ExpandConstant('{app}') +  '\VistaLib64.dll' )
  else
    path := AddQuotes( ExpandConstant('{app}') +  '\VistaLib32.dll' );

  //MsgBox('path: ' + path, mbInformation, MB_OK);
  Result := path;
end;


// These don't work
//procedure RunNonElevated32( hWnd: Integer; file, params, dir: String );
//external 'RunNonElevated@files:VistaLib32.dll';


//procedure RunNonElevated64( hWnd: Integer; file, params, dir: String );
//external 'RunNonElevated@files:VistaLib64.dll';


procedure CurUninstallStepChanged(CurStep: TUninstallStep);
var
  batfile: String;
  uninstallers: TArrayOfString;
  arrayLen: Integer;
  lineIdx: Integer;
  currentLine: String;
  processExitCode: Integer;
  execOK: Boolean;
begin
  if (CurStep = usUninstall) then
  begin

    QuitHelper(False);

    // Uninstall the plugins
    batfile := ExpandConstant('{commonappdata}\Last.fm\Client\uninst2.bat');
    LoadStringsFromFile(batfile, uninstallers);
    //MsgBox('loaded string array', mbInformation, MB_OK);

    arrayLen := GetArrayLength(uninstallers) - 1;
    for lineIdx := 0 to arrayLen do
    begin
      currentLine := uninstallers[lineIdx];

      if (Pos('start', currentLine) = 1) then
      begin
        // Old style entry, convert from OEM codepage and strip junk
        OemToCharBuff(currentLine);
        Delete(currentLine, 1, 16);

        //MsgBox('deleted front: ' + currentLine, mbInformation, MB_OK);

        Delete(currentLine, Pos('"', currentLine), Length(currentLine) - Pos('"', currentLine) + 1 );

        //MsgBox('deleted back: ' + currentLine, mbInformation, MB_OK);

        //MsgBox('old style, trying: ' + currentLine, mbInformation, MB_OK);

        execOK := Exec(currentLine, '/SILENT', '', SW_SHOW, ewWaitUntilTerminated, processExitCode);
        //if (execOK = True) then MsgBox('OEM exec successful', mbInformation, MB_OK)
        //else MsgBox('OEM exec failed', mbInformation, MB_OK);
      end else
      begin
        //MsgBox('execing line: ' + currentLine, mbInformation, MB_OK);
        execOK := Exec(currentLine, '/SILENT', '', SW_SHOW, ewWaitUntilTerminated, processExitCode);
        //if (execOK = True) then MsgBox('exec successful', mbInformation, MB_OK)
        //else MsgBox('exec failed', mbInformation, MB_OK);
      end;

    end; // end of loop

    // Run Cleaner
    //Exec( 'RunDll32.exe', GetPathVistaDll('') + ',RunNonElevated ' + AddQuotes( ExpandConstant( '{app}' ) + '\Cleaner.exe' ), '', SW_HIDE, ewWaitUntilTerminated, processExitCode );

    // Horrible, but there's no way of ensuring that the script waits for the Cleaner to finish.
    // This is still not enough. Big caches take some time to wipe.
    //Sleep( 5000 );

  end; // end of CurStep = usUninstall

end;
