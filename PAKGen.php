<?php
//==============================================================================
//
// Author:  Sean Sullivan
// Created:	02 January 2002
//
// This file contains proprietary and company secret information that must
// not be disclosed to any third party.
//
// Copyright: © 2002 Pata-Sucia Ltd. All rights reserved.
//
//==============================================================================

//------------------------------------------------------------------------------
// This is the main function to generate a Product Access Key (PAK)
// for WBPR 2.1
//------------------------------------------------------------------------------
function PakWBPR21Generate ()
{
	$NewPak = new Pak();
	$NewPak->Users = 1;
	$NewPak->ProductName = "WinBlitProofRead";
	return $NewPak->get_Code();
}

//------------------------------------------- -----------------------------------
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
	var $Guid;
	var $ProductName;
	var $SizeData;
	var $SizeDigest;

	//------------------------------------------------------------------------------
	function Pak()
	{
		$this->IsValid = false;
		$this->Digest = "";
		$this->Users = 0;					// Unlimited
		$this->Guid = "12345678901234567890123456789012"; // Secret ID that makes this algorithm unique to me (this is not the one I use)
		$this->ProductName = "";
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
	function put_Code($PakIn, $ProductName)
	{
		$Pak = CleanHex($PakIn);
		$this->IsValid = false;
		$this->ProductName = $ProductName;

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
		return strtoupper
				(
					substr
					(
						str_pad
						(
							md5($Data . $this->Guid . $this->ProductName ),
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

		$Data = str_pad($Data, $this->SizeData*4, "0", STR_PAD_RIGHT);
		return str_pad(ConvertBinHex($Data), $this->SizeData, "0", STR_PAD_LEFT);
	}


	//------------------------------------------------------------------------------
	function p_put_Data($DataIn)
	{
		$Data = str_pad(ConvertHexBin($DataIn), $this->SizeData*4, "0", STR_PAD_LEFT);
	}


	//------------------------------------------------------------------------------
	function cmp_Data($PakIn)
	{
		$Result = true;

		if ($this->Users != $PakIn->Users) $Result = false;

		return $Result;
	}


	//------------------------------------------------------------------------------
	function dbg_Print()
	{
		echo "<br/>IsValid: " . $this->IsValid;
		echo "<br/>Users: " . $this->Users;
	}
}


?>
