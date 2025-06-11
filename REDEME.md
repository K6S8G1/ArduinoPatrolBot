# ArduinoPatrolBot

**ArduinoPatrolBot** to autonomiczny robot mobilny oparty na Arduino UNO R4 WiFi, który realizuje:

- 🚗 śledzenie linii przy pomocy algorytmu Bang-Bang
- 🌐 komunikację przez WiFi/WebSocket
- 📦 zapis danych pomiarowych do plików `map.csv` i `patrol.csv` na karcie microSD
- 📊 przesyłanie i wizualizację danych przez stronę hostowaną z tej samej karty microSD i mikrokontroler Arduino

----------------------------------------------------------------------------------------------

## 🔧 Wymagane biblioteki Arduino

- `WiFiS3` – komunikacja WiFi
- `WebSocketsServer` – obsługa WebSocket
- `SD` – odczyt/zapis z karty microSD
- `SPI` – komunikacja z kartą SD

Zainstaluj je z poziomu **Library Managera** w Arduino IDE.

----------------------------------------------------------------------------------------------

## 🚀 Jak uruchomić

1. **Skompiluj i wgraj kod:** użyj `ArduinoPatrolBot.ino` jako pliku głównego.
2. **Skopiuj pliki z folderu `sdcard/`** na sformatowaną kartę microSD (FAT32).
3. **Włóż kartę SD do robota**.
4. **Uruchom robota – będzie:**
   - łączyć się z WiFi,
   - uruchamiać serwer WWW/WebSocket,
   - rejestrować dane pomiarowe,
   - patrolować lub mapować zależnie od trybu.

----------------------------------------------------------------------------------------------

## 📄 Pliki danych

- `map.csv` – dane z trybu mapowania (z odległościami i przebytymi drogami)
- `patrol.csv` – dane z patrolu (analogiczne, ale w innym trybie)
- generowane są automatycznie na karcie SD

----------------------------------------------------------------------------------------------

## 📜 Licencja

Projekt jest udostępniony na licencji MIT – możesz go swobodnie modyfikować, rozpowszechniać i wykorzystywać, z zachowaniem praw autorskich.

----------------------------------------------------------------------------------------------

## 🧠 Autor

Projekt wykonany jako część pracy inżynierskiej. Kod modularny, przejrzysty i gotowy do rozbudowy o: PID, obsługę RFID, czy SLAM.
Projek wykazał, że platforma Arduino nie jest adekwatnym wyborem dla projektów robotów autonomicznych ze względu na ograniczoną ilość pinów I/O oraz
ograniczoną moc obliczeniową, która znacząco zmniejsza możliwości 
