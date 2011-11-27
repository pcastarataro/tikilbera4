/*
 * Base64EncoderDecoder.h
 *
 *  Created on: 04/11/2011
 *      Author: pablo
 */

#ifndef BASE64ENCODERDECODER_H_
#define BASE64ENCODERDECODER_H_

#include <string>

/**
 * Clase encargada de codificar y decodificar una cadena con Base64
 * Esta codificacion es la utilizada por las autentificacion del http
 */
class Base64EncoderDecoder {
public:
	std::string base64_chars;

	inline bool is_base64(unsigned char c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}

public:
	/**
	 * Constructor
	 */
	Base64EncoderDecoder() {
		Base64EncoderDecoder::base64_chars
				= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	}

	/**
	 * Destructor
	 */
	~Base64EncoderDecoder() {
	}

	/**
	 * Codifica una cadena en base64
	 * @param cadena a codificar
	 * @return cadena codificada
	 */
	std::string codificar(const std::string& cadena) {
		const unsigned char* bytes_to_encode =
				(const unsigned char*) cadena.c_str();
		unsigned int in_len = cadena.size();
		std::string ret;
		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		while (in_len--) {
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4)
						+ ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2)
						+ ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for (i = 0; (i < 4); i++)
					ret += base64_chars[char_array_4[i]];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4)
					+ ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2)
					+ ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (j = 0; (j < i + 1); j++)
				ret += base64_chars[char_array_4[j]];

			while ((i++ < 3))
				ret += '=';
		}
		return ret;
	}

	/**
	 * Decodifica una cadena en base64
	 * @param cadena a decodificar
	 * @return cadena decodificada
	 */
	std::string decodificar(const std::string & cadena) {
		int in_len = cadena.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::string ret;

		while (in_len-- && (cadena[in_] != '=') && is_base64(cadena[in_])) {
			char_array_4[i++] = cadena[in_];
			in_++;
			if (i == 4) {
				for (i = 0; i < 4; i++)
					char_array_4[i] = base64_chars.find(char_array_4[i]);

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1]
						& 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4)
						+ ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6)
						+ char_array_4[3];

				for (i = 0; (i < 3); i++)
					ret += char_array_3[i];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j < 4; j++)
				char_array_4[j] = 0;

			for (j = 0; j < 4; j++)
				char_array_4[j] = base64_chars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2)
					+ ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4)
					+ ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++)
				ret += char_array_3[j];
		}
		return ret;
	}
};
#endif /* BASE64ENCODERDECODER_H_ */
