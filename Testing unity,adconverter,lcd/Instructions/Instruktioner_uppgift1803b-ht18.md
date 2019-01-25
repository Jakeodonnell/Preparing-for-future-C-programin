Instruktioner - uppgift 1803b-ht18
======


_Ulrik Eklund, 2015-09-04_  
_Tommy Andersson, 2017-11-17_


Översikt och syfte med uppgiften:
------
I den här uppgiften kommer du att använda Arduino Due kortet tillsammans med en LCD-shield med några tryckknappar. Beroende på vilken knapp som trycks ner fås en analog spänning som kan avläsas med A/D-omvandlaren i SAM3XE-controllern. När programmeringen är klar skall ditt program reagera på knapptryckningar och skriva ut på displayen vilken knapp som tryckts ner.
På vägen dit skall du träna dig mer i användning av Atmel Studio, Git och TDD och bland annat lära dig:

1. Hur man bygger upp större program med flera filer.
2. Hur binära tal kan omvandlas och skrivas ut med ASCII-tecken.
3. Hur en timer fungerar och används.
4. Hur A/D-omvandlaren kan användas.


Utförande:
----
Uppgiften görs två och två, och ni förväntas arbeta i samma grupper som i laboration 1803a.

Som vanligt så innehåller all mjukvara buggar, troligtvis även det exempelprojekt som labben utgår ifrån (och till och med denna labbhandledning). 
Se det som en del av labben att eliminera eventuella existerande buggar om de påträffas!

Krav för godkänt:
------
Ha genomfört följande labbmoment enligt denna handledning:

1. Ladda ner labbens kodexempel från github (enligt instruktioner ni tidigare fått)
2. Kompilera och ladda ner det existerande programmet till Due-kortet
3. Köra programmet och se testerna fallera
4. Implementerat funktioner för LCD-displayen så att testerna passeras:
    - Rensa LCD
    - Skriva ut fyra siffror på LCD
5. Implementera funktioner för A/D-omvandlaren så att testerna passeras:
    - Initialisera A/D-omvandlaren
    - Läsa värde från A/D-omvandlaren
6. Implementera funktioner för knappsatsen på LCD-shielden så testerna passeras:
    - Tolka värde från A/D-omvandlaren till en specifik knapp
7. Ta bort kommentarerna för någon av de oändliga looparna i main.c och se värdet på LCD:n ändras beroende på vilken knapp som trycks in
8. Pusha kod + tester till ditt  github-classroom-repo.



Förberedelser
------

#### Instudering

Labben kommer att innehålla C-programmering för att komma åt olika typer av in- och utgångar och hur man skapar och testar lämpliga abstraktioner för dessa. Mer specifikt kommer du att behöva kunna, utöver vad som gick igenom till föregående laboration:

- Hur man skapar större projekt med flera filer (sektion 5 i [1]).
	- Skillnaden mellan deklarationer och definitioner av funktioner och praxis i vilka filer man gör detta
	- Vad som är scope för en variabel beroende på var den definieras. Vad `static`och `extern` betyder.

- Förstå hela byggprocessen för ett C-program i ett inbyggt system, från kompilering via länkning till flashning av microcontrollern.

- Känna till hur pinnarna på Arduino Due förhåller sig till utgångarna på SAM3X8E [4].

- Känna till vilka hårdvaruregister (sektion 36 i [3]) och bibliotek i [Atmel Software Framework](http://asf.atmel.com/docs/latest/search.html?board=Arduino%20Due/X) som används att styra timer counter (TC) på en SAM3X8E Cortex-M3 mikrocontroller. Den används för att implementera en enkel funktion `delayMicroseconds()` som väntar en specifik tid.

- Känna till vilka hårdvaruregister (sektion 31 i [3]) och bibliotek i [ASF](http://asf.atmel.com/docs/latest/search.html?board=Arduino%20Due/X) som används för att styra digitala utgångar på en SAM3X8E Cortex-M3 mikrocontroller. Det finns en enkel funktion `lcdWrite()` som använder sig av dessa utgångar för att styra Hitachi HD44780U Dot Matrix Liquid Crystal Display Controller[5] för att driva displayen på Arduino-shielden. `lcdWrite()` skriver i sin enklaste användning en enstaka [ascii-symbol](http://www.asciitable.com) på displayen.

- Känna till vilka hårdvaruregister(sektion 43 i [3]) och bibliotek i [Atmel Software Framework](http://asf.atmel.com/docs/latest/search.html?board=Arduino%20Due/X) som används att läsa A/D-ingången på en SAM3X8E Cortex-M3 mikrocontroller. Här används den för att avkoda knapparna på LCD-shielden (se kretsschema i [6]).

- Tester för C-funktioner [8]

Det finns ett diagnostiskt test på Canvas. Gör det innan du går till labbsalen som en koll på att du kan grunderna!


Du skall också ha läst igenom hela denna handledning innan du går till labbsalen!

Själva uppgiften
------

Skapa ett personligt repo för denna programmeringsuppgift med hjälp av Git på samma sätt som i uppgift 1803a. 

#### Arbetskatalogen för denna uppgiften

I arbetskatalogen denna laboration finns mappen `Instructions` och en projektmapp för Atmel studio vid namn `ProjectShield`.


### Labbsetup

Utrustning:

- Utvecklingskort Arduino Due
- USB-kabel
- [LCD shield för Arduino](http://www.dfrobot.com/index.php?route=product/product&path=35_124&product_id=51#.Vcs3mosiYdI)

För att skydda A/D-ingången från överspänning har ett extra motstånd lötts till som gör att inspänningen håller sig inom tillåtet område. **OBS! Om man använder en shield direkt från affären som inte modifierats riskerar man att föstöra Due-kortet!**


### Labbens programmeringsuppgift
När du klonat git-repot, vi antar här att ni klonat till katalogen `Assignment1803b_ht18` finns nu katalogen `Assignment1803b_ht18\ProjectShield` på din lokala dator. Glöm inte att initiera Git i katalogen och addera filerna på samma sätt som i uppgift 1803a.
I katalogen finns en projektfil för Atmel Studio, som ni öppnar genom ”open project” inifrån Atmel Studio.

Labben går ut på att ni ska skriva funktioner som passerar de testfall som finns definierade i projektet.  
Testa först att kompilera projektet under menyn _Build_. Det här kollar främst att syntaxen är rätt, variabler är definierade och lite annat. C har annars få begränsningar vad som är rätt eller fel i språket.

Ladda ner den färdiga binärfilen till Due-kortet via USB-kabeln med kommandot _BossacArduinoDue(Debug)_ under Tools-menyn. 

#### Test-driven utveckling (Test-Driven Development TDD)
I labben är stegen redan givna för alla testerna. 
##### Förberedelse

1. En testlista  är gjord för den här labben! Testerna är
    - The delay timer is initialised properly
    - The delay timer counts properly
    - The LCD display is initialised
    - It is possible to write a single character to the LCD display  (actually writes 12 characters)
    - It is possible to erase all text on the LCD display
    - The A/D converter input is initialised properly
    - The A/D converter input reads a reasonable value when no button is pressed (should not be zero)
    - A function reads a value and interprets that no button is pushed (from a set of values in a struct)
    - A function displays a four digit int number on the LCD display 
    - A function displays a string on the LCD display 
    - A function displays what button is pressed on the LCD display
    
2. c–filer och motsvarande .h-filer med funktionerna som skall testas är redan gjort för modulerna som skall testas, de ligger i katalogen src.

##### Testcykeln

3. Välj ett test från testlistan (gör dem i samma ordning som de står i testrunner.filen `main.c`)
4. Skriv/uppdatera testfilen för funktionen som ska testas (redan gjort för de flesta testerna, men några kan behövas kompletteras)
5. ”runner-filen” som exekverar valda tester finns redan, `main.c` (all testerna körs från början, men alla passerar inte)
6. Kompilera
7. Ladda ner det kompilerade programmet till Due-kortet
8. Kör programmet på Due-kortet
9. Se testen fallera, för det finns ju inget innehåll i den funktion som ska testas. För att resultatet ska synas måste ett terminalfönstret  vara installerat (finns i Atmel Studio på datorerna i labbsalen).
10. Skriv programkoden så att funktionen klarar av testet (lägg till kod i respektive fil i src)
11. Kompilera och kör
12. Se testen/testerna passera, annars upprepa 8-9.
13. Städa och eventuellt kommentera din kod om det inte redan är gjort.

##### Samla ihop resultaten från TDD-cykeln

14. Committa till ditt personliga repo (valfritt)
15. Upprepa testcykeln tills alla tester i testlistan är implementerade. Då är även de två funktionerna färdigprogrammerade!

#### Exempel på hur det ser ut för de tester som redan har implementerad kod: Delay-timern
Projektet har två kataloger som man jobbar mot, `src` och `test`. Funktionerna man utvecklar ligger i `src`. Testrunner-filen `main.c` och filerna med testerna ligger i katalogen `test`. Testramverket unity ligger i katalogen `unity`.   
Det finns redan funktioner för delay-timern i `delayFunctions.c` och `delayFunctions.h`, motsvarande tester för dessa funktioner finns i `test_delayFunctions.c` och `test_delayFunctions.h`, dessa tester exekverar redan från runner-filen.  
_Observera att man måste använda ASF Wizard under ASF menyn för att inkludera Atmels bibliotek för timern (TC) för att dessa ska fungera._

När man sen vill använda sina testade filer i produktionssystemet behöver man bara filerna i src-katalogen. Testfilerna används alltså bara under utveckling.

##### En enkel testfil
Alla testfunktioner är av typen
```c
void test_TheFunctionsdoesSomethingUseful(void);
```

Dessa tester deklareras snyggast i en motsvarande h-fil för att inkluderas i runner-filen (se nedan). 

I det här projektet finns det 3 filer med c-kod för tester, de innehåller totalt 9 tester, varav endast de som testar delay passeras.  
Testrunner-filen som kör testerna är projektets huvudfil, eftersom det är den här filen som allting körs ifrån måste den innehålla `main()`. Den måste också innehålla all nödvändig initiering av Due-kortet själv, många av de initialisationsfunktionerna kommer från Atmels ASF-bibliotek.

Det står kommenterat i `main()`var själva testramverket Unity börjar användas. Det är här det första testet körs.
När man lägger till fler tester görs det efter befintliga tester, men innan `UnityEnd();`  
Om man har flera källkodsfiler med tester har man ett par av `UnityBegin()` / `UnityEnd()` för varje fil.

#### Se resultatet från testerna

Eftersom det inte finns någon naturlig bildskärm kopplad till Due-kortet måste man få ut testresultaten på annat sätt.

I början på testrunner-filen finns hur man initierar att Due-kortet skriver på COM-porten på PC:n via USB-kabeln (`configure_console(void)`). Det gör det möjligt att använda terminalfönstret inifrån Atmel Studio som output för putchar() som Unity använder sig av. Men Terminalfönstret konkurrerar med Bossac om COM-porten så när man laddar ner sin binärfil till DUE-kortet måste terminalfönstret vara o-connectat (i Atmel Studio görs detta automatiskt).  Så fort man laddat ner sin binärfil till Due så startar ju programmet och därför missar man utskriften innan man gjort connect igen. Gör connect och tryck på reset-knappen för att starta testrunner-programmet om igen.Om allt funkar som det ska ser du att Unity meddelar resultatet från testerna i terminalfönstret. Det går också att spara resultaten från terminalfönstret i en fil, vilket kommer att utnyttjas till inlämningen.

### Utveckling av funktioner för att använda LCD-display med Arduino

I filerna `LCDFunctions.c` och `lcdApplication.c` finns sex funktioner redan definierade, men det saknas kod i de fyra sista av dem som du ska skriva för att testerna ska passeras. När funktionen funkar så kommer också testerna att passeras.
**OBS!** Skriv rutinerna i samma ordning som testerna körs. Det underlättar...

```c
int lcdInit(void);
int lcdWrite(uint8_t byte, bool type);
int lcdClearDisplay(void);
int lcdWrite4DigitNumber(int number);
int lcdWriteAsciiString(const char *string);
int lcdWriteButtonValue(buttonType inputButton)
```

#### int lcdInit(void)
Den här funktionen klar, den är en implementering i C av hur man initierar en LCD-display som styrs av Hitachi HD44780U (Dot Matrix Liquid Crystal Display Controller/Driver).  
Själva algoritmen beskrivs i Figur 24 på sidan 46 i databladet [5].

LCD-shielden som man sätter på Due-kortet har bara 4 datapinnar kopplade, så efter att den omkonfigurerats till 4-bitas användning används `lcdWrite()` för att skicka data till displayen.

Tyvärr är inte pinnen som gör att man kan läsa status på LCD-shielden kopplad (pinne R/W), annars hade man använt den för att ge output till funktionen. Nu är funktionen implementerad på enklast möjliga sätt och ger ifrån sig 0 när den löpt igenom alla instruktionerna.

#### int lcdWrite(uint8_t byte, bool type);
Funktionen är redan klar. Den skriver en byte till LCD-displayen. Om `type == HIGH` tolkas det som att ett tecken ska skrivas, om `type == LOW` tolkas det som att ett kommando skickas till displayen. Det som skrivs ut på displayen är ASCII-tecknet för det värde som byte innehåller (<http://www.asciitable.com>).  
Funktionen abstraherar bort två saker för programmeraren som använder den:

- Att LCD-shielden använder bara 4 pinnar i stället för 8.
- Att LCD-shielden, som är konstruerad för  Arduino Uno-kort, har pinnarna i omvänd ordning jämfört med Arduino Due.  

Funktionen gör att tecknen och kommandona till LCD-displayen kan programmeras rakt av enligt tabellerna 4 och 6 i referensmanualen till Hitachi-controllern.
Utvärdet från funktionen följer samma konvention som för Unix script, dvs 0 om allt går som det ska, i praktiken ger denna funktion alltid ifrån sig 0.

#### int lcdClearDisplay(void)
Skriv en enkel funktion, `lcdClearDisplay(void)`, som rensar displayen och flyttar tillbaka markören till startpositionen. Funktionen kan t.ex. ge ifrån sig värdet 0 när den är klar (unix-standard för en funktion som inte ger några fel).  
Information hur det görs finns i tabell 6 i databladet till controllern för LCD-displayen [5]. Titta till exempel på de fem sista raderna i funktionen InitLCD() i projektet.


#### int lcdWrite4DigitNumber(int number)
Skriv funktionen `lcdWrite4DigitNumber()` som tar ett fyrsiffrigt heltal som argument och skriver ut det som fyra på varandra följande bytes kodade i ASCII på displayen, t.ex. med hjälp av `lcdWrite()`.
Tips: Det tar tid för displayen att hantera varje tecken. Tyvärr finns ingen "ready"-signal utan man måste i stället lägga in lämpliga delayer.
Testet för denna funktion kollar att den sista skrivna siffran är rätt, men du kan också se att värdet skrivs på displayen när testet körs (1357).
Funktionen bör ge ifrån sig värde 0 om den fungerar som det ska.

#### int lcdWriteAsciiString(const char *string)
Skriv funktionen `lcdWriteAsciiString(const char *string)`som tar en textsträng som argument och skriver ut den på displayen. Du bestämmer själv den maximalt tillåtna längden på strängen.
Tips: Som ovan.
Testet för denna funktion kollar att det sista skrivna tecknet är rätt, men du kan också se att strängen skrivs på displayen när testet körs ("Test everything!").
Funktionen bör ge ifrån sig värde 0 om den fungerar som det ska.

#### int lcdWriteButtonValue(buttonType inputButton)
Skriv funktionen `lcdWriteButtonValue(buttonType inputButton)`som tar en variabel av buttonType och skriver ut en textsträng med motsvarande namn ("SELECT", "LEFT" osv.).
Testet för denna funktion kollar att det sista skrivna tecknet är rätt, men du kan också se att strängen skrivs på displayen när testet körs ("SELECT").
Funktionen bör ge ifrån sig värde 0 om den fungerar som det ska.

### Programmering: A/D-omvandlaren

Skriv funktioner för att initialisera A/D-omvandlaren i motsvarande c/h-filer.
Det första testet anropar funktionen `analogInit(0)` eftersom knappsatsen är kopplad till Due-pinne A0. Du ska skriva `analogInit(int pinNumber)` , men kan alltså förutsätta att inparametern är 0. Testet kollar att rätt statusbitar är satta i hårdvaran för den ingången som används efter att funktionen har körts.

Dokumentation och kodexempel för AD-omvandlaren finns på Atmels sida för ASF (<http://asf.atmel.com/docs/latest/sam3x/html/sam_adc_quickstart.html>, man behöver inte implementera några interrupts!).

Efter initiering av A/D-omvandlaren krävs det få programrader för att läsa ett värde från A/D-omvandlaren, men du bör ändå skriva en funktion som kapslar in detta. Det andra testet kollar att värdet från A/D-omvandlaren är rimligt med tanke på att ingen knapp är intryckt (värdet varierar lite mellan olika LCD-shields eftersom motstånd inte är exakt lika stora). _Obs att A/D-omvandlaren aldrig ger ifrån sig värdet 0 (eftersom ingången inte kan ha värdet 0 enligt kopplingsschemat för knappsatsen på LCD-shielden)._

Tänk på att man måste initiera klockan för att A/D-omvandlaren ska snurra! Det finns en kodrad för det redan i projektet. A/D-omvandlaren har en egen klocka, precis som de flesta andra perifera enheter på processorns och de klockorna sätts inte på automatiskt om de inte behövs för att spara ström. Man kan till exempel titta på koden i `delayFunctions.c` där klockan för timer counter 0 initialiseras.

```c
void delay_init(void)	/*Initializes the timer used for delays */
{
           pmc_enable_periph_clk(ID_TC0);
           ...
}
```

A/D-omvandlarens klocka startas med precis samma funktion, men med ett annat ID-argument (ID_ADC).  
Det står i den Quick Start Guide för A/D-omvandlaren som finns på Atmels hemsida att det här måste göras under Prerequsites.

### Programmering: Sätta samman allt
Nu har du skrivit testade funktioner för att kunna visa på displayen och kunna läsa från knappsatsen på shielden, men någon test återstår.
Innan du fortsätter med de rutiner som behövs så ta bort kommentarerna på följande rader i `main()`:

```c
//while(1)
//{
//	/* Infinite loop to display the current valued from the ADC reading the buttons */
//	lcdClearDisplay(void);
//	uint32_t tempValue = analogRead(0);
//	lcdWrite4DigitNumber(tempValue);
//	delayMicroseconds(500000);
//}
```

Då kommer värde för knappen som trycks in att skrivas ut på displayen och ändras när en annan knapp trycks in.

Fortsätt nu med de funktioner som behövs för att återstående tester skall passeras.

Till slut: skriv ett program med en loop som ligger och läser av knapparna och skriver ut aktuell knapptryckning kontinerligt. Lägg det sist i main().

Nu har du klarat av all programmering som behövs (men det är lite kvar med själva inlämningen för att få godkänt). Visa gärna upp Due-kortet med LCD-displayen för handledaren om du befinner dig i labbsalen.  


### Ladda upp arbetet på github för bedömning 
När ni är klara med er uppgift skall ni pusha alla ändringar till ert  repository på Github, enligt instruktion i dokumentet _DA267A - laboratory environment_. En viktig sak som måste göras är att lägga till eventuella nya filer till ditt repo (som `testResultat.txt`). 
Har du kommit så långt har du ett uppdaterat repo som du kan se på githubs webbsida. 

Ni skall också redovisa uppgiften för en av kursens labbhandledare, vilket ni helst gör under kursens laborationstillfällen. Under redovisningen skall ni visa att koden fungerar och gruppens alla medlemmar måste kunna förklara vad som gjorts. 


Läraren kommer att titta på alla som har lämnat in till onsdag kväll veckan efter den schemalagda handledningen. Om du lämnar in senare kommer inlämningen att bedömas i samband med tentan vid kursens slut. När ni är klara och har pushat er slutgiltiga kod till Github måste ni meddela labbhandledare att ni är klara via laborationes inlämningssida på Canvas. 


Referenser
------
[1] Nick Parlante, Essential C, 2003, http://cslibrary.stanford.edu/101/

[2] C data types, https://en.wikipedia.org/wiki/C_data_types 

[3] Atmel SAM3X / SAM3A Series SMART ARM-based MCU DATASHEET, 2015, <http://www.atmel.com/devices/sam3x8e.aspx> 

[4] SAM3X-Arduino Pin Mapping, <http://www.arduino.cc/en/Hacking/PinMappingSAM3X> 

[5] Hitachi HD44780U Dot Matrix Liquid Crystal Display Controller/Driver reference manual, <https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller> and <https://www.sparkfun.com/datasheets/LCD/HD44780.pdf>

[6] DF Robot, LCD KeyPad Shield For Arduino product wiki, <http://www.dfrobot.com/wiki/index.php/LCD_KeyPad_Shield_For_Arduino_SKU:_DFR0009> 

[7] Dan Saks, Representing and Manipulating Hardware in Standard C and C++, Embedded Systems Conference San Francisco, 2002, <http://www.open-std.org/jtc1/sc22/wg21/docs/ESC_SF_02_465_paper.pdf> 

[8] Mark VanderVoord, Embedded Testing With Unity And Cmock - A Book For Those Who Code C And Want Awesome Well-Tested Products Using Free Tools And For Those Who Enjoy Short Books with Long Titles, 2010

Appendix: A/D channels versus Due pin mapping
------
Instance | Signal | I/O Line | Peripheral | Due Pin---|---|---|---|---
ADC | ADTRG | PA11| BADC | AD0 | PA2 | X1| Analog In 7ADC | AD1/WKUP1| PA3| X1| Analog In 6 ADC | AD2| PA4| X1 | Analog In 5ADC | AD3| PA6| X1| Analog In 4ADC | AD4 | PA22 | X1| Analog In 3ADC | AD5 | PA23 | X1 | Analog In 2ADC | AD6 | PA24 | X1 | Analog In 1ADC | AD7 | PA16 | X1 | Analog In 0ADC | AD8 | PB12 | X1ADC | AD9 | PB13 | X1ADC | AD10 | PB17 | X1 | Analog In 8ADC | AD11 | PB18 | X1 | Analog In 9ADC | AD12 | PB19 | X1 | Analog In 10ADC | AD13 | PB20 | X1 | Analog In 11ADC | AD14/WKUP13 | PB21 | X1Appendix: Output från programmet
------
Eftersom det inte finns någon naturlig bildskärm kopplad till Due-kortet måste man få ut saker som vanligtvis skulle skrivas på en terminal på annat sätt.

I `ConsoleFunctions.c` finns ett exempel hur man initierar att Due-kortet skriver på COM-porten på PC:n via USB-kabeln (`configure_console(void)`). Det gör det möjligt att använda terminalfönstret inifrån Atmel Studio som output för `printf()`.  
Det finns dock ingen motsvarande h-fil, så den måste man skriva själv!

Man måste dessutom inkludera Atmels biblotek för seriell I/O med hjälp av ASF wizard i Atmel Studio. Parametrarna för terminalkommunikationen måste man ange i filen `config/conf_uart_serial.h* som genereras av ASF wizard när man inkluderar biblioteket. Enklast är att använda default-parametrarna genom att bara ta bort kommentarsymbolerna.

Terminalfönstret konkurrerar med Bossac om COM-porten så när man laddar ner sin binärfil till DUE-kortet måste terminalfönstret vara o-connectat.  
Så fort man laddat ner sin binärfil till Due så startar ju programmet och därför missar man utskriften innan man gjort connect igen. Gör connect och tryck på reset-knappen för att starta programmet om igen.


