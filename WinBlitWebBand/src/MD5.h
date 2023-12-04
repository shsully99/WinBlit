// MD5.h: interface for the CMD5 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MD5_H__12960C77_552B_43C8_B158_83C19BBC8078__INCLUDED_)
#define AFX_MD5_H__12960C77_552B_43C8_B158_83C19BBC8078__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMD5  
{
public:
	bool ValidatePAK (const char*, const char *);
	CMD5();
	virtual ~CMD5();


	CMD5(const char* plainText);  //set plaintext in ctor
	void setPlainText(const char* plainText); //set plaintext with a mutator, it's ok to 
				                              //to call this multiple times, the digest is recalculated after each call.
	const char* getMD5Digest();	  //access message digest (aka hash), return 0 if plaintext has not been set


private:
	bool calcDigest(); //this function computes the digest by calling the RFC 1321 'C' code

	bool m_digestValid; //false until the plaintext has been set and digest computed
	unsigned char  m_digest[16]; //the numerical value of the digest
	char  m_digestString[33];  //Null terminated string value of the digest expressed in hex digits
	char* m_plainText; //a pointer to the plain text.  If casting away the const-ness 
	                   //worries you, you could either make a local copy of the plain 
	                   //text string instead of just pointing at the user's string or 
					   //modify the RFC 1321 code to take 'const' plaintext. 

};

#endif // !defined(AFX_MD5_H__12960C77_552B_43C8_B158_83C19BBC8078__INCLUDED_)
