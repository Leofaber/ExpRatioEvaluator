# ExpRatioEvaluator

Traduzione della routine exp-ratio, attualmente eseguita con script shell che utilizza tool esterni.
Questa routine permette di valutare quando una “detection” o “spot” è troppo vicina ai bordi dell’esposure AGILE.
Restituisce un numero compreso tra 0 e 1 (1 bad).
In particolare si definisce exp-ratio come:

	exp-ratio = nBad/nTot; 
	
	nBad -> numero di pixels in una regione rettangolare i cui valori non sono compresi in un certo range dato in input alla routine
	nTot -> numero di pixels della regione rettangolare

La routine exp-ratio è stata incapsulata nella classe ExpRatioEvaluator che deve essere instanziata chiamando il seguente costruttore:
	
	ExpRatioEvaluator(const char * _expPath, double minTreshold, double maxTreshold, double l, double b);

Per calcolare exp-ratio si deve chiamare il metodo: 

	double computeExpRatioValues();

che ritorna il seguente array:

	[ exp-ratio, nBad, totCount, greyLevelsMean ]


### Dipendenze:

	CFitsio: 
	Per l'apertura del file Fits. 

	AgileMap:
	Si utilizzano le funzione di conversione pixel->coordinate galattiche e viceversa.
	
