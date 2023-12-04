<?php
//==============================================================================
//
// Author:  Patricia Pothecary
// Created:	02 January 2002
//
// This file is provided by Total Recall Ltd soley for the use by regsoft.com
// of providing customers with registration codes (PAKs) in order that the 
// customers are able to fully use Total Recall software.
//
// This file contains proprietary and company secret information that must
// not be disclosed to any third party.
//
// Copyright: © 2002 Total Recall Ltd. All rights reserved.
//
//
// Description:
//
// The public entry point is the function Pak1Autoweb0102Generate.
//
// This function uses the email address passed as an argument in order to
// generate a Product Access Key that is specific to:
//		1. The provided email address (case insensitive)
//		2. Total Recall Autoweb version 1.02
//		3. regsoft.com
//		4. Today's date
//
//==============================================================================

//------------------------------------------------------------------------------
// This is the main function to generate a Product Access Key (PAK)
// for Autoweb version 1.02
//------------------------------------------------------------------------------
function Pak1Autoweb0102Generate ($Email)
{
	$NewPak = new Pak();

	$NewPak->Users = 1;
	$NewPak->IssueChannel = 1;
	$NewPak->ProductLevel = 1;
	$NewPak->ProductVersion = 1;

	$NewPak->ProductName = "Autoweb";
	$NewPak->Email = $Email;

	return $NewPak->get_Code();
}


//------------------------------------------------------------------------------
$HexChars = "0123456789ABCDEF";


//------------------------------------------------------------------------------
// Convert a binary string to a Hex string
//------------------------------------------------------------------------------
function ConvertBinHex ($InString)
{
	$bin = $InString;


	// Pad the binary string to a whole number of 4-bit groups
	$rem = strlen($bin) % 4; if ($rem > 0) $rem = 4 - $rem;
	$bin = str_pad($bin, strlen($bin) + $rem, "0", STR_PAD_LEFT);


	// Step through the 4-bit groups converting each to Hex
	global $HexChars;
	$Hex = "";
	for ($i=0; $i<strlen($bin); $i+=4)
	{
		$digit = substr($bin,$i,4);
		if ($Hex != "" || $digit != "0000")
		{
			$Hex .= substr($HexChars,bindec($digit),1);
		}
	}
	if ($Hex == "") $Hex = "0";


	// Return the result
	return $Hex;
}


//------------------------------------------------------------------------------
// Convert a Hex string to a binary string
//------------------------------------------------------------------------------
function ConvertHexBin ($InHex)
{
	$Bin = "";
	global $HexChars;


	// Expand each Hex digit into 4 bits of binary
	for ($i=0; $i<strlen($InHex); $i++)
	{
		$digit = substr($InHex,$i,1);
		$Bin .= str_pad(decbin(strpos($HexChars, $digit)), 4, "0", STR_PAD_LEFT);
	}


	// Return the result
	return $Bin;
}


//------------------------------------------------------------------------------
// Clean up an inputted hex string
//------------------------------------------------------------------------------
function CleanHex ($InString)
{
	$InString = strtoupper($InString);
	$String = "";
	for ($i=0; $i<strlen($InString); $i++)
	{
		$Char = substr($InString, $i, 1);
		if ($Char == 'I') $Char = '1';
		if ($Char == 'O') $Char = '0';
		if ($Char == 'S') $Char = '5';
		if ($Char == 'Z') $Char = '2';
		if (($Char >= '0' && $Char <= '9') || ($Char >= 'A' && $Char <= 'F'))
		{
			$String .= $Char;
		}
	}
	return $String;
}


//==============================================================================
class Pak
{
	var $IsValid;
	var $Digest;

	var $IssueTime;
	var $IssueChannel;
	var $Duration;
	var $ExpiryTime;
	var $Users;
	var $ProductLevelUpgrade;
	var $ProductLevel;
	var $ProductVersionUpgrade;
	var $ProductVersion;
	var $Component;

	var $Guid;
	var $Time0;
	var $ProductName;
	var $Email;

	var $SizeData;
	var $SizeDigest;


	//------------------------------------------------------------------------------
	function Pak()
	{
		$this->IsValid = false;
		$this->Digest = "";

		$this->IssueTime = time();			// Today
		$this->IssueChannel = 0;			// Direct
		$this->Duration = 0;				// Unlimited
		$this->ExpiryTime = 0;				// Never
		$this->Users = 0;					// Unlimited
		$this->ProductLevelUpgrade = 0;		// Not an upgrade
		$this->ProductLevel = 0;			// Universal
		$this->ProductVersionUpgrade = 0;	// Not an upgrade
		$this->ProductVersion = 0;			// Universal
		$this->Component = array();
		$this->Component[0] = true;		// Includes main program

		$this->Guid = "12345678901234567890123456789012"; // Secret ID that makes this algorithm unique to me (this is not the one I use)
		$this->Time0 = mktime(0,0,0,1,1,2002);
		$this->ProductName = "";
		$this->Email = "";

		$this->SizeData = 14;
		$this->SizeDigest = 11;
	}


	//------------------------------------------------------------------------------
	function get_Code()
	{
		// Get the data as a string
		$Data = $this->p_get_Data();


		// Update the data with modified values
		$this->p_put_Data($Data);


		// Append the MD5 digest
		$this->Digest = $this->p_get_Digest($Data);
		$Pak = $Data . $this->Digest;


		// This is now a valid Pak
		$this->IsValid = true;


		// Format the output string
		$PakOut = substr($Pak, 0, 5);
		$PakOut .= "-" . substr($Pak, 5, 5);
		$PakOut .= "-" . substr($Pak, 10, 5);
		$PakOut .= "-" . substr($Pak, 15, 5);
		$PakOut .= "-" . substr($Pak, 20, 5);


		return $PakOut;
	}


	//------------------------------------------------------------------------------
	function put_Code($PakIn, $ProductName, $Email)
	{
		$Pak = CleanHex($PakIn);
		$this->IsValid = false;
		$this->ProductName = $ProductName;
		$this->Email = $Email;

		$Data = substr($Pak, 0, $this->SizeData);
		$Digest = substr($Pak, $this->SizeData, $this->SizeDigest);


		// Extract the data from the code
		$this->p_put_Data($Data);


		// Extract the Digest
		$this->Digest = $Digest;


		// Check the digest
		if ($Digest == $this->p_get_Digest($Data)) $this->IsValid = true;


		return $this->IsValid;
	}


	//------------------------------------------------------------------------------
	function p_get_Digest($Data)
	{
		$this->ProductName = strtoupper($this->ProductName);
		$this->Email = strtoupper($this->Email);
		return strtoupper
				(
					substr
					(
						str_pad
						(
							md5($Data . $this->Guid . $this->ProductName . $this->Email),
							$this->SizeDigest, 
							"0", 
							STR_PAD_LEFT
						),
						0, 
						$this->SizeDigest
					)
				);
	}


	//------------------------------------------------------------------------------
	function p_get_Data()
	{
		$Data = "";
		$DurationDay = 60 * 60 * 24;


		// Append the issue day number
		$DayNumber = (int)(($this->IssueTime - $this->Time0) / $DurationDay);
		$Data .= str_pad(decbin($DayNumber), 13, "0", STR_PAD_LEFT);


		// Append the issue channel number
		$Data .= str_pad(decbin($this->IssueChannel), 4, "0", STR_PAD_LEFT);


		// Append the licenced duration (in months)
		$Data .= str_pad(decbin($this->Duration), 5, "0", STR_PAD_LEFT);


		// Append the licenced number of users (=(x-1)^2)
		$Users = $this->Users;
		$Rem = false;
		$i = 0;
		while ($Users > 1)
		{
			$i++;
			if (($Users%2) == 1) $Rem = true;
			$Users = (int)($Users / 2);
		}
		if ($Rem) $i++;
		if ($Users > 0) $i++;
		$Data .= str_pad(decbin($i), 4, "0", STR_PAD_LEFT);


		// Append the licenced product level upgrade
		$Data .= str_pad(decbin($this->ProductLevelUpgrade), 2, "0", STR_PAD_LEFT);


		// Append the licenced product level
		$Data .= str_pad(decbin($this->ProductLevel), 2, "0", STR_PAD_LEFT);


		// Append the licenced product version upgrade
		$Data .= str_pad(decbin($this->ProductVersionUpgrade), 10, "0", STR_PAD_LEFT);

		
		// Append the licenced product version
		$Data .= str_pad(decbin($this->ProductVersion), 10, "0", STR_PAD_LEFT);


		// Append the components
		for ($Idx = 0; $Idx < 6; $Idx++)
		{
			if (isset($this->Component[$Idx]) && $this->Component[$Idx])
			{
				$Data .= "1";
			}
			else
			{
				$Data .= "0";
			}
		}


		$Data = str_pad($Data, $this->SizeData*4, "0", STR_PAD_RIGHT);
		return str_pad(ConvertBinHex($Data), $this->SizeData, "0", STR_PAD_LEFT);
	}


	//------------------------------------------------------------------------------
	function p_put_Data($DataIn)
	{
		$DurationDay = 60 * 60 * 24;
		$Data = str_pad(ConvertHexBin($DataIn), $this->SizeData*4, "0", STR_PAD_LEFT);
		$Pos = 0;


		// Extract the issue time
		$DayNumber = bindec(substr($Data, $Pos, 13));
		$Pos += 13;
		$this->IssueTime = $this->Time0 + ($DayNumber * $DurationDay);


		// Extract the issue channel number
		$this->IssueChannel = bindec(substr($Data, $Pos, 4));
		$Pos += 4;


		// Extract the licenced duration (in months)
		$this->Duration = bindec(substr($Data, $Pos, 5));
		if ($this->Duration > 0)
		{
			$this->ExpiryTime = $this->IssueTime + ($this->Duration * 31 + 2) * $DurationDay;
		}
		else
		{
			$this->ExpiryTime = 0;
		}
		$Pos += 5;


		// Extract the licenced number of users (=(x-1)^2)
		$Users = bindec(substr($Data, $Pos, 4));
		$Pos += 4;
		if ($Users == 0)
		{
			$this->Users = 0;
		}
		else
		{
			$this->Users = pow(2, ($Users-1));
		}


		// Extract the licenced product level upgrade
		$this->ProductLevelUpgrade = bindec(substr($Data, $Pos, 2));
		$Pos += 2;


		// Extract the licenced product level
		$this->ProductLevel = bindec(substr($Data, $Pos, 2));
		$Pos += 2;


		// Extract the licenced product version upgrade
		$this->ProductVersionUpgrade = bindec(substr($Data, $Pos, 10));
		$Pos += 10;


		// Extract the licenced product version 
		$this->ProductVersion = bindec(substr($Data, $Pos, 10));
		$Pos += 10;

		
		// Extract the components
		for ($Idx = 0; $Idx < 6; $Idx++)
		{
			if (substr($Data, $Pos, 1) == "1")
			{
				$this->Component[$Idx] = true;
			}
			else
			{
				$this->Component[$Idx] = false;
			}
			$Pos++;
		}


		//echo "<br/>Pos = ".$Pos;
	}


	//------------------------------------------------------------------------------
	function cmp_Data($PakIn)
	{
		$Result = true;

		if ($this->IssueTime != $PakIn->IssueTime) $Result = false;
		if ($this->IssueChannel != $PakIn->IssueChannel) $Result = false;
		if ($this->Duration != $PakIn->Duration) $Result = false;
		if ($this->Users != $PakIn->Users) $Result = false;
		if ($this->ProductLevelUpgrade != $PakIn->ProductLevelUpgrade) $Result = false;
		if ($this->ProductLevel != $PakIn->ProductLevel) $Result = false;
		if ($this->ProductVersionUpgrade != $PakIn->ProductVersionUpgrade) $Result = false;
		if ($this->ProductVersion != $PakIn->ProductVersion) $Result = false;

		return $Result;
	}


	//------------------------------------------------------------------------------
	function dbg_Print()
	{
		echo "<br/>IsValid: " . $this->IsValid;
		echo "<br/>IssueTime: " . date("d-M-Y H:i:s", $this->IssueTime);
		echo "<br/>IssueChannel: " . $this->IssueChannel;
		echo "<br/>Duration: " . $this->Duration;
		echo "<br/>ExpiryTime: " . date("d-M-Y H:i:s", $this->ExpiryTime);
		echo "<br/>Users: " . $this->Users;
		echo "<br/>ProductLevelUpgrade: " . $this->ProductLevelUpgrade;
		echo "<br/>ProductLevel: " . $this->ProductLevel;
		echo "<br/>ProductVersionUpgrade: " . $this->ProductVersionUpgrade;
		echo "<br/>ProductVersion: " . $this->ProductVersion;
		foreach($this->Component as $Key => $Value)
		{
			if ($Value)
			{
				echo "<br/>Component[$Key]: true";
			}
			else
			{
				echo "<br/>Component[$Key]: false";
			}
		}
	}
}


?>
