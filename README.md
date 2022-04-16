# Proiect_SE_2022

/*
	In cadrul programului s-au folosit:
	5 mesaje de tipul unsigned char,
	variabile tip long pentru termenii operatiei de efectuat: Op1, Op2
	Key pentru a stoca rezultatul conversiei caracterului receptionat pe UART spre numar
	Calc unde se stocheaza rezultatul operatiei
	
	un buffer de tip unsigned char in care se va pastra rezultatul operaetiei dupa conversia de la char la intreg (long)
	pointer de tip unsigned char care poate fi folosit pentru trimming-ul spatiilor albe din buffer-ul de afisare (neimplementat)
	i si j pentru folosirea lor in cadrul unor bucle for
	
	Intregul cod ruleaza intr-o bucla infinita unde secvential se petrec urmatoarele actiuni:
		*Se afiseaza un mesaj de introducere
		*Se cere introducerea primului numar:
			- Se face intr-o bucla (caracter cu caracter) ce se va opri atunci cand se detecteaza apasarea tastei Enter
			- La fiecare iteratie se converteste din caracter in numar
		*Se cere introducerea celui de-al doilea numar
			- Se repeta aceeasi secventa ca si in cazul primului numar
		*Se cere introducerea operatiei dorite (+, -, *, /)
			- In cazul default (introducerea altui caracter decat cele precizate) se va efectua suma
			- Se stocheaza rezultatul operatiei
		*Se realizeaza conversia rezultatului
		*Se afiseaza rezultatul operatiei
		
	Aditional, se folosesc functiile deja prezentate in laboratoare pentru configurarea UART-ului, clock.. etc
	
	Singurele aditii sunt:
		- stdout_getchar(unsigned char echo):
			echo = 0 sau 1; pentru 1 se va trimite inapoi caracterul receptionat, altfel nu
		- LongToStr(long l, unsigned char* buffer):
			realizeaza conversia parametrului l in codul ASCII si stocarea acestuia in buffer in vederea afisarii ulterioare
		- void br()
			trimite newline si carriage return
	
*/
