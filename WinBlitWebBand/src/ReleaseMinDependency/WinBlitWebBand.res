        ˙˙  ˙˙                  Ź      ˙˙ ˙˙     0 	        Ź4   V S _ V E R S I O N _ I N F O     ˝ďţ               ?                            S t r i n g F i l e I n f o   č   0 4 0 9 0 4 b 0       C o m m e n t s   >   C o m p a n y N a m e     P a t a - S u c i a   l t d     T   F i l e D e s c r i p t i o n     W i n B l i t W e b B a n d   M o d u l e   6   F i l e V e r s i o n     2 ,   4 ,   0 ,   0     >   I n t e r n a l N a m e   W i n B l i t W e b B a n d     B   L e g a l C o p y r i g h t   C o p y r i g h t   2 0 0 1     (    L e g a l T r a d e m a r k s     (    O L E S e l f R e g i s t e r     N   O r i g i n a l F i l e n a m e   W i n B l i t W e b B a n d . D L L          P r i v a t e B u i l d   L   P r o d u c t N a m e     W i n B l i t W e b B a n d   M o d u l e   :   P r o d u c t V e r s i o n   2 ,   4 ,   0 ,   0          S p e c i a l B u i l d   D    V a r F i l e I n f o     $    T r a n s l a t i o n     	°č      ˙˙ ˙˙     0	        (       @                                              ŔŔŔ    ˙  ˙   ˙˙ ˙   ˙ ˙ ˙˙  ˙˙˙                     f   f   fff   fff   fff   fff   fff   fff   fff   fff   f   f                                                                                                                                                   (      ˙˙ ˙˙     0	        (                Ŕ                                      ŔŔŔ    ˙  ˙   ˙˙ ˙   ˙ ˙ ˙˙  ˙˙˙  wwpwpwwpf`wpf`wpf`wpf`wwpwpw                                                                 "       ˙˙ ˙˙É     0	                 č      (     č      ˙˙ ˙˙     0	        (       @                                              ŔŔŔ    ˙  ˙   ˙˙ ˙   ˙ ˙ ˙˙  ˙˙˙ wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww  wwwwwwwwwwwwww  wwwwwwwwwwwww ˙˙ wwwwwwwwwwww ˙˙ wwwwwwwwwww ˙˙˙˙ wwwwwwwwww ˙˙˙˙ wwwwwwwwww ˙˙˙˙  wwwwwwwww ˙˙˙˙  wwwwwwwww ˙˙˙ Ě wwwwwww ˙˙˙ Ě wwwwww ˙˙˙ ĚĚĚ wwwww ˙˙˙ ĚĚĚ wwwww ˙˙˙ ĚĚĚ www ˙˙˙ ĚĚĚ www ˙˙˙ ĚĚĚ www ˙˙˙ ĚĚĚ www ˙˙˙ ĚĚĚ wwwww ˙˙˙ ĚĚĚ wwwwww ˙˙˙ Ě wwwwwww ˙˙˙ Ě wwwwwww ˙˙˙˙  wwwwwwwww ˙˙˙˙  wwwwwwwww ˙˙˙˙ wwwwwwwwww ˙˙˙˙ wwwwwwwwwww ˙˙ wwwwwwwwwwww ˙˙ wwwwwwwwwwwww  wwwwwwwwwwwwww  wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww                                                                                                                                (      ˙˙ ˙˙     0	        (                Ŕ                                      ŔŔŔ    ˙  ˙   ˙˙ ˙   ˙ ˙ ˙˙  ˙˙˙ wwwwwwwwww wwwwwwp˙wwwww˙đwwwww˙đwwww˙wwp˙đĚŔwwp˙đĚŔwp˙đĚŔwp˙đĚŔwww˙www˙đwwww˙đwwwwwp˙wwwwww wwwwwwwwwwwww                                                                "       ˙˙ ˙˙Ę     0	                 č      (       0   R E G I S T R Y   ˙˙f       0	        HKCR
{
	WinBlitWebBand.ExplorerBand.1 = s 'WinBlit Explorer Band'
	{
		CLSID = s '{326215A4-58C1-11D5-8601-508750000000}'
	}
	WinBlitWebBand.ExplorerBand = s 'WinBlit Explorer Band'
	{
		CLSID = s '{326215A4-58C1-11D5-8601-508750000000}'
		CurVer = s 'WinBlitWebBand.ExplorerBand.1'
	}
	NoRemove CLSID
	{
		ForceRemove {326215A4-58C1-11D5-8601-508750000000} = s 'WinBlit Explorer Band'
		{
			ProgID = s 'WinBlitWebBand.ExplorerBand.1'
			VersionIndependentProgID = s 'WinBlitWebBand.ExplorerBand'
			ForceRemove 'Programmable'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
			'TypeLib' = s '{155F89E1-568F-11D5-85FA-C6EA86000000}'
			'Implemented Categories'
			{
				{00021493-0000-0000-C000-000000000046}
				{
				}
			}
		}
	}
}
HKLM
{
	SOFTWARE
	{
		Microsoft
		{	
			'Internet Explorer'
			{
				NoRemove Extensions
				{
					ForceRemove {42125B80-58C8-11d5-8602-4E809D000000}
					{
						ForceRemove val HotIcon = s '%MODULE%,202'
						ForceRemove val Icon = s '%MODULE%,201'
						ForceRemove val ButtonText = s 'WinBlitExplorerBand'
						ForceRemove val 'Default Visible' = s 'Yes'
						ForceRemove val CLSID = s '{E0DD6CAB-2D10-11D2-8F1A-0000F87ABD16}'										
						ForceRemove val BandCLSID =  s '{326215A4-58C1-11D5-8601-508750000000}'
						ForceRemove val MenuText = s 'WinBlit Explorer Band' 
						ForceRemove val MenuStatusBar = s 'WinBlit Explorer Band' 
					}
				}
			}
		}
	}
}
HKEY_LOCAL_MACHINE
{
	NoRemove 'Software'
	{
		NoRemove 'Microsoft'
		{
			NoRemove 'Internet Explorer'
			{
				NoRemove 'Explorer Bars'
				{
					ForceRemove '{326215A4-58C1-11D5-8601-508750000000}'
					{
						val BarSize = b '8001000000000000'
					}
				}
			}
		}
	}
}
 Ó  0   R E G I S T R Y   ˙˙g       0	        HKCR
{
	WinBlitWebBand.CommBand.1 = s 'WinBlit Comm Band'
	{
		CLSID = s '{326215A6-58C1-11D5-8601-508750000000}'
	}
	WinBlitWebBand.CommBand = s 'WinBlit Comm Band'
	{
		CLSID = s '{326215A6-58C1-11D5-8601-508750000000}'
		CurVer = s 'WinBlitWebBand.CommBand.1'
	}
	NoRemove CLSID
	{
		ForceRemove {326215A6-58C1-11D5-8601-508750000000} = s 'WinBlit Comm Band'
		{
			ProgID = s 'WinBlitWebBand.CommBand.1'
			VersionIndependentProgID = s 'WinBlitWebBand.CommBand'
			ForceRemove 'Programmable'
			InprocServer32 = s '%MODULE%'
			{
				val ThreadingModel = s 'Apartment'
			}
			'TypeLib' = s '{155F89E1-568F-11D5-85FA-C6EA86000000}'
			'Implemented Categories'
			{
				{00021494-0000-0000-C000-000000000046}
				{
				}
			}
		}
	}
}
HKLM
{
	SOFTWARE
	{
		Microsoft
		{	
			'Internet Explorer'
			{
				NoRemove Extensions
				{
					ForceRemove {7FBFF7F0-58C8-11D5-8602-4E809D000000}
					{
						ForceRemove val HotIcon = s '%MODULE%,202'
						ForceRemove val Icon = s '%MODULE%,201'
						ForceRemove val ButtonText = s 'WinBlit'
						ForceRemove val 'Default Visible' = s 'Yes'
						ForceRemove val CLSID = s '{E0DD6CAB-2D10-11D2-8F1A-0000F87ABD16}'										
						ForceRemove val BandCLSID =  s '{326215A6-58C1-11D5-8601-508750000000}'
						ForceRemove val MenuText = s 'WinBlit Comm Band' 
						ForceRemove val MenuStatusBar = s 'WinBlit Comm Band' 
					}
				}
			}
		}
	}
}
HKEY_LOCAL_MACHINE
{
	NoRemove 'Software'
	{
		NoRemove 'Microsoft'
		{
			NoRemove 'Internet Explorer'
			{
				NoRemove 'Explorer Bars'
				{
					ForceRemove '{326215A6-58C1-11D5-8601-508750000000}'
					{
						val BarSize = b 'B800000000000000'
					}
				}
			}
		}
	}
}
 $  ,   T Y P E L I B   ˙˙     0 	        MSFT      	      A                            K       ˙˙˙˙                    d   Č   ,  T    ˙˙˙˙   \     ˙˙˙˙   h     ˙˙˙˙   <      ˙˙˙˙   ä     ˙˙˙˙   d  Ř   ˙˙˙˙        ˙˙˙˙     Ź   ˙˙˙˙   0     ˙˙˙˙   ˙˙˙˙    ˙˙˙˙   ˙˙˙˙    ˙˙˙˙   Ŕ     ˙˙˙˙   Đ     ˙˙˙˙   ˙˙˙˙    ˙˙˙˙   ˙˙˙˙    ˙˙˙˙   %"  č      ˙˙˙˙                           H              $           ˙˙˙˙                  ˙˙˙˙4" č      ˙˙˙˙                              @  8       8           ˙˙˙˙              ˙˙˙˙%" č      ˙˙˙˙                           ¨      T       T           ˙˙˙˙                 ˙˙˙˙4" č  P   H                             Ŕ   @  h       d           ˙˙˙˙               ˙˙˙˙˙˙˙˙    x   ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙`      H   Ŕ   ¨   ˙˙˙˙0   ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙   á_VŐúĆę   ţ˙˙˙˙˙˙˙cşwŢ|QŃ˘Ú  řw<é˙˙˙˙˙˙˙˙dşwŢ|QŃ˘Ú  řw<é˙˙˙˙˙˙˙˙¤b2ÁXŐPP       ˙˙˙˙0     Ŕ      F   ˙˙˙˙      Ŕ      F   ˙˙˙˙Łb2ÁXŐPP   d   ˙˙˙˙Śb2ÁXŐPP   Č   ˙˙˙˙Ľb2ÁXŐPP   ,  ˙˙˙˙d      ˙˙˙˙˙˙˙˙,     ˙˙˙˙˙˙˙˙      x   `          - stdole2.tlbWWW˙˙˙˙        ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙   ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙   ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙8   ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙T   ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙h   ˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙˙ °WINBLITWEBBANDLibWWW    ˙˙˙˙8LExplorerBandd   ˙˙˙˙8[#IExplorerBandWWWČ   ˙˙˙˙8wCommBand,  ˙˙˙˙	8ýICommBandWWW,  ˙˙˙˙ ŠSetDocumentW˙˙˙˙˙˙˙˙ "!pDispWWW WinBlitWebBand 1.0 Type LibraryWWW ExplorerBandClassW IExplorerBand InterfaceWWW CommBandClassW ICommBand InterfaceWWW method SetDocument Ň*=WW ¤ WW       ˙˙˙˙0          ,   ,         D 	         |   	 	                 <       ˙˙ ˙˙     0	                 W i n B l i t W e b B a n d                       