# ExpRatioEvaluator 1.0.5

Traduzione della routine exp-ratio, attualmente eseguita con script shell che utilizza tool esterni.
Questa routine permette di valutare quando una “detection” o “spot” è troppo vicina ai bordi dell’esposure AGILE.
Restituisce un numero compreso tra 0 e 100 (0 bad).

In particolare si definisce exp-ratio come:

	exp-ratio = (1 -  nBad/nTot)*100; 
	
	nBad -> numero di pixels in una regione rettangolare i cui valori non sono compresi in un certo range dato in input alla routine
	nTot -> numero di pixels della regione rettangolare

Per rendere indipendente la mappa dal tempo di esposizione, si normalizza dividendo ogni pixel per un normalizationFactor.
	
	normalizationFactor = timeFactor*spatialFactor

        timeFactor = tStop - tStart
        spatialFactor = 0.0003046174197867085688996857673060958405 * cdelt2 * cdelt2


La routine exp-ratio è stata incapsulata nella classe ExpRatioEvaluator che deve essere instanziata chiamando il seguente costruttore:
	
	ExpRatioEvaluator(const char * _expPath,bool normalize, double minTreshold, double maxTreshold, double l, double b);

	Se normalize == true allora si calcola l'exp-ratio sulla mappa normalizzata.


Per calcolare exp-ratio si deve chiamare il metodo: 

	double computeExpRatioValues();

che ritorna il seguente array:

	[ exp-ratio, nBad, totCount, greyLevelsMean ]


### Dipendenze:

	CFitsio: 
	Per l'apertura del file Fits. 

	AgileMap:
	Si utilizzano le funzione di conversione pixel->coordinate galattiche e viceversa

### Esempio Normalizzazione (prima riga della matrice di valori della mappa exp):
	
	NON normalizzata: 8.55229 8.48367 8.41506 8.43352 8.45197 8.46707 8.48217 8.492 8.50182 8.50961 8.51739 8.52386 8.53033 8.53547 8.54062 8.54394 8.54726 8.54008 8.5329 8.52273 8.51255 8.54708 8.58161 8.61895 8.65628 8.5777 8.49913 8.50764 8.51615 8.523 8.52986 8.5352 8.54053 8.54302 8.54551 8.542 8.5385 8.52689 8.51528 8.49808 8.48089 8.46036 8.43983 8.41705 8.39428 8.36798 8.34167 8.23662 8.13157 8.16113 8.19069 8.22094 8.2512 8.24105 8.23091 8.21738 8.20384 8.18152 8.1592 8.13268 8.10616 8.07796 8.04976 8.01948 7.9892 7.95574 7.92228 7.84201 7.76173 7.69158 7.62142 7.59228 7.56314 7.53232 7.50151 7.46681 7.43211 7.43764 7.44317 7.44721 7.45125 7.41352 7.3758 7.33472 7.29365 7.25003 7.20641 7.15902 7.11163 6.99235 6.87308 6.83646 6.79983 6.75876 6.71769 6.67216 6.62662 6.57739 6.52816 6.47713 
 

	normalizzata: 112.302 111.401 110.5 110.742 110.985 111.183 111.381 111.51 111.639 111.742 111.844 111.929 112.014 112.081 112.149 112.192 112.236 112.142 112.047 111.914 111.78 112.234 112.687 113.177 113.668 112.636 111.604 111.716 111.827 111.917 112.007 112.078 112.148 112.18 112.213 112.167 112.121 111.968 111.816 111.59 111.364 111.095 110.825 110.526 110.227 109.882 109.536 108.157 106.777 107.166 107.554 107.951 108.348 108.215 108.082 107.904 107.727 107.433 107.14 106.792 106.444 106.074 105.703 105.306 104.908 104.469 104.029 102.975 101.921 101 100.079 99.6959 99.3132 98.9086 98.504 98.0483 97.5927 97.6653 97.738 97.791 97.844 97.3487 96.8533 96.3139 95.7745 95.2018 94.629 94.0067 93.3844 91.8182 90.252 89.7711 89.2902 88.7508 88.2115 87.6136 87.0157 86.3692 85.7228 85.0527 


	 
 	
