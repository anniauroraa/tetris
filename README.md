# Tetris
Tetris-peli, joka on kirjoitettu Ohjelmointi 2 -kurssia varten. Kieli on C++ ja UI framework Qt.

![Kuvakaappaus pelistä](images/tetris.png)

## Kurssilla vaadittu perustoiminnallisuus
- Peli alkaa start-nappia painamalla.
- Tetris-palikka valikoituu satunnaisesti saatavilla olevista seitsemästä palikasta ja asettuu pelialueen yläreunaan.
- Tetris-palikka tippuu kokoajan tietyllä nopeudella alas päin, kunnes se osuu maahan tai toiseen palikkaan, sitten se pysähtyy.
- Tetris-palikka ei käänny, se voi kuitenkin liikkua oikealle tai vasemmalle nappeja painamalla (right- ja left-napit) niin kauan kunhan se pysyy pelialueella.
- Kun pelissä painaa nappia down, sen hetkinen tetris-palikka tippuu suoraan niin alas kuin se vain pääsee.
- Peli loppuu, kun uusi tetris-palikka ei enää mahdu pelialueelle osumatta muihin palikoihin ja käyttöliittymään ilmestyy teksti "Game over!" (ylös saattaa jäädä yksi tyhjä rivi, jos seuraavaksi tuleva tetris-palikka oliai vienyt kaksi riviä, eikä kahta riviä ollut enää vapaana).

## Lisätoiminnallisuus
- Pelissä on kaikki seitsemän tetris-palikkaa.
- Pelissä on ajastin, joka näyttää peliin kuluneen ajan samalla kun peli on käynnissä.
- Pelissä on down-nappi, eli palikat tippuvat suoraan alas sitä painamalla.
- Tetris-palikkaa pystyy vielä kerran liikuttamaan vaakatasossa, vaikka se on laskeutunut pohjan tai toisen tetris-palikan päälle. Vasta tämän jälkeen toinen palikka ilmestyy pelialueelle.
- Pelissä on restart-ominaisuus, eli pelin loputtua käyttöliittymään ilmestyy restart-nappi, jolla voi aloittaa pelin alusta.