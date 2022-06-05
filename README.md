# Ölçme ve Enstrümantasyon Proje

# E-posta Bildirimleri ile ESP32 Kapı Durumu İzleme (IFTTT)

Bu projede, bir ESP32 kartı ve bir manyetik anahtar (reed switch) kullanarak bir kapının durumunu izleyeceğiz. Kapının durumu değiştiğinde açık veya kapalı olarak bir e-posta bildirimi alacağız. E-posta bildirimleri IFTTT kullanılarak gönderilecek.


#  Projeye Genel Bakış

Kapının açık veya kapalı olup olmadığını algılamak için kolayca bir kapıya, pencereye veya çekmeceye uygulayabileceğimiz plastik bir kabuk içine yerleştirilmiş bir manyetik anahtarı kullanacağız.
![enter image description here](https://image.made-in-china.com/202f0j00bVZYwnydKlcs/Fbmc32-Magnetic-Reed-Switch-Sensor.jpg)
Anahtarın yakınında bir mıknatıs olduğunda elektrik devresi kapanır—kapı kapalıdır. Mıknatıs anahtardan çok uzakta olduğunda (kapı açıkken) devre açıktır.

##   IFTTT ile E-posta Gönderme

ESP32 ile e-posta göndermek için SMTP server'a alternatif olarak IFTTT adlı bir hizmeti kullanacağız. IFTTT ile uygulamaların birlikte çalışmasını sağlayabiliriz. Örneğin, IFTTT'ye belirli bir istek göndermek, size bir e-posta uyarısı göndermek gibi bir uygulamayı tetikler.  Kaynak kodun içinde bulunması gereken IFTTT ssid, password ve apikey bilgilerimi IFTTT hesabımın güvenliği için paylaştığım koddan kaldırdım.

##  Parça listesi

İşte bu projeyi tamamlamak için ihtiyacımız olan donanım:

 - ESP32
 - 1 × Manyetik Reed Anahtarı
 - 1× 10kΩ direnç
 - 1 × breadboard
 - Jumper Kablolar

##   Şematik – Reed Anahtarlı ESP32


![enter image description here](https://i0.wp.com/randomnerdtutorials.com/wp-content/uploads/2021/09/ESP32-Reed-Switch-door-sensor-circuit.png?resize=578,500&quality=100&strip=all&ssl=1)

  Manyetik anahtarı GPIO 4'e bağladık, ancak uygun herhangi bir GPIO'ya bağlayabiliriz.
