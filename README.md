# ExpRatioEvaluator 1.0.10

La routine exp-ratio permette di valutare quando una “detection” o “spot” è troppo vicina ai bordi dell’esposure AGILE.
Restituisce un numero compreso tra 0 e 100 (0 bad).

In particolare si definisce exp-ratio come:

    exp-ratio = (1 -  nBad/nTot)*100;
    
    nBad -> numero di pixels in una regione rettangolare i cui valori non sono compresi in un certo range dato in input alla routine
    nTot -> numero di pixels della regione rettangolare

Per rendere indipendente la mappa dal tempo di esposizione, si può decidere di normalizzarla, dividendo ogni pixel per un normalizationFactor.
    
    normalizationFactor = timeFactor*spatialFactor
    
    timeFactor = tStop - tStart
    spatialFactor = 0.0003046174197867085688996857673060958405 * cdelt2 * cdelt2 * Alikesinaa(0.0174532925199432954743716805978692718782 * distanceFromCenter);

### Utilizzo

La routine exp-ratio è stata incapsulata nella classe ExpRatioEvaluator che deve essere instanziata chiamando i seguenti costruttori:
	
	ExpRatioEvaluator(const char * expPath, bool onNormalizedMap, bool createExpRatioMap);
	
	ExpRatioEvaluator(const char * expPath, bool onNormalizedMap, bool createExpRatioMap, double minThreshold, double maxThreshold, int squareSize);
	
	ExpRatioEvaluator(AgileMap agileMap, bool onNormalizedMap, bool createExpRatioMap);
	
	ExpRatioEvaluator(AgileMap agileMap, bool onNormalizedMap, bool createExpRatioMap, double minThreshold, double maxThreshold, int squareSize);


### Parametri del costruttore

    expPath : il path alla mappa (.exp, .cts, .exp.gz, .cts.gz)
    
    agileMap : la mappa di tipo AgileMap
    
    onNormalizedMap : se il valore è true, si assume che la mappa exp in input NON sia normalizzata. Il software provvederà a normalizzarla e le successive valutazioni (il calcolo expratio e la creazione della exp-ratio map) verranno effettuate sulla mappa normalizzata.
    
    createExpRatioMap : se è true verrà creata la mappa exp-ratio.
    
    minThreshold : la soglia minima per la creazione della mappa exp-ratio. (Se onNormalizedMap==true -> default 100 else default 0)
    
    maxThreshold : la soglia minima per la creazione della mappa exp-ratio. (Se onNormalizedMap==true -> default 120 else default 140)
    
    squareSize : la dimensione dell'area di analisi exp-ratio. Le dimensioni del lato del quadrato sono calcolate come squareSize = _squareSize/cdelt2;  (default 20)


Per calcolare exp-ratio si deve chiamare il metodo:

    double computeExpRatioValues(double l, double b);

    l : longitudine galattica 
	
    b : latitudine galattica

### Output costruttore

Il costruttore crea e scrive su file due mappe a seconda dei parametri di input:

	Se onNormalizedMap == true, crea la mappa normalizzata il cui filename sarà:  expPath + "_norm.exp.gz", apribile con ds9
  
	Se createExpRatioMap == true, crea la mappa exp-ratio (in cui ogni pixel è un exp-ratio centrato sul pixel stesso) il cui filename sarà: expPath + "_norm_exp.gz" con ds9
	
### Output metodo computeExpRatioValues(double l, double b);
	
	il valore exp-ratio
    

### Altre funzioni:

Versione overload di computeExpRatioValues(..): si utilizza per non passare dalla conversione (l,b) -> (x,y) ma applicare direttamente la valutazione exp-ratio su (x,y). Type può essere una stringa qualsiasi.
    
    double* computeExpRatioValues(int x, int y, string type);
           
    
### Dipendenze:

   "FitsUtil.h"
   Per l'apertura e la creazione dei file Fits.

    AgileMap: "AgileMap.h"
    Si utilizzano le funzione di conversione pixel->coordinate galattiche e viceversa

### Esempio Normalizzazione (prima riga della matrice di valori della mappa exp):
    
    NON normalizzata: 8.55229 8.48367 8.41506 8.43352 8.45197 8.46707 8.48217 8.492 8.50182 8.50961 8.51739 8.52386 8.53033 8.53547 8.54062 8.54394 8.54726 8.54008 8.5329 8.52273 8.51255 8.54708 8.58161 8.61895 8.65628 8.5777 8.49913 8.50764 8.51615 8.523 8.52986 8.5352 8.54053 8.54302 8.54551 8.542 8.5385 8.52689 8.51528 8.49808 8.48089 8.46036 8.43983 8.41705 8.39428 8.36798 8.34167 8.23662 8.13157 8.16113 8.19069 8.22094 8.2512 8.24105 8.23091 8.21738 8.20384 8.18152 8.1592 8.13268 8.10616 8.07796 8.04976 8.01948 7.9892 7.95574 7.92228 7.84201 7.76173 7.69158 7.62142 7.59228 7.56314 7.53232 7.50151 7.46681 7.43211 7.43764 7.44317 7.44721 7.45125 7.41352 7.3758 7.33472 7.29365 7.25003 7.20641 7.15902 7.11163 6.99235 6.87308 6.83646 6.79983 6.75876 6.71769 6.67216 6.62662 6.57739 6.52816 6.47713
 

    normalizzata: 112.302 111.401 110.5 110.742 110.985 111.183 111.381 111.51 111.639 111.742 111.844 111.929 112.014 112.081 112.149 112.192 112.236 112.142 112.047 111.914 111.78 112.234 112.687 113.177 113.668 112.636 111.604 111.716 111.827 111.917 112.007 112.078 112.148 112.18 112.213 112.167 112.121 111.968 111.816 111.59 111.364 111.095 110.825 110.526 110.227 109.882 109.536 108.157 106.777 107.166 107.554 107.951 108.348 108.215 108.082 107.904 107.727 107.433 107.14 106.792 106.444 106.074 105.703 105.306 104.908 104.469 104.029 102.975 101.921 101 100.079 99.6959 99.3132 98.9086 98.504 98.0483 97.5927 97.6653 97.738 97.791 97.844 97.3487 96.8533 96.3139 95.7745 95.2018 94.629 94.0067 93.3844 91.8182 90.252 89.7711 89.2902 88.7508 88.2115 87.6136 87.0157 86.3692 85.7228 85.0527

    mappa exp-ratio: -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 70.4938 69.7799 69.1255 68.7091 68.5901 68.5901 68.6496 68.7091 68.7091 68.8281 69.0065 69.185 69.423 69.6014 69.7799 69.8394 69.8989 69.8989 69.6014 68.9471 68.2927 67.6383 66.9839 66.3296 65.7347 65.3778 65.0208 64.7829 64.6639 64.4854 64.307 64.1285 63.95 63.8311 63.7121 63.6526 63.5931 63.5336 63.4741 63.3551 63.2362 63.1172 62.8792 62.5818 62.0464 61.1541 60.2023 59.2504 58.3581 57.5253 56.633 55.6217 54.4319 53.1826 51.9929 50.7436 49.5538 48.3046 47.0553 45.8061 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1

### Esempi di output:

    computeExpRatioValues(double l, double b);

	Mappa non normalizzata, minTheshold: 10, maxThreshold: 11
    exp.computeExpRatioValues(30,30);
    exp-ratio: 47.6502 
    nBad, totCount, greyLevelsMean   880 1681 9.93831

	Mappa non normalizzata, minTheshold: 0, maxThreshold: 100
    exp.computeExpRatioValues(30,30);
    exp-ratio: 100 0
    nBad, totCount, greyLevelsMean 1681 9.93831

    Mappa non normalizzata, minTheshold: 0, maxThreshold: 5
    exp.computeExpRatioValues(30,30);
    exp-ratio: 0
    nBad, totCount, greyLevelsMean 1681 1681 9.93831


	Mappa normalizzata, minTheshold: 50, maxThreshold: 150
    exp.computeExpRatioValues(30,30);
    exp-ratio: 100 
    nBad, totCount, greyLevelsMean 0 1681 130.502

	Mappa normalizzata, minTheshold: 129, maxThreshold: 131
    exp.computeExpRatioValues(30,30);
    exp-ratio: 16.2403 
    nBad, totCount, greyLevelsMean 1408 1681 130.502

	Mappa normalizzata, minTheshold: 0, maxThreshold: 50
    exp.computeExpRatioValues(30,30);
    exp-ratio: 0 
    nBad, totCount, greyLevelsMean 1681 1681 130.502

### Codici di errore

    -1  :  l'area di valutazione (rettangolo) esce fuori dalla mappa.
    -2  :  le coordinate (l,b) su cui si centra l'area di valutazione escono fuori dalla mappa. Può essere causato dal fatto che le coordinate (l,b) sono il centroide di un blob estratto da una mappa il cui centro non coincide con la relativa mappa di esposizione.

    
     


