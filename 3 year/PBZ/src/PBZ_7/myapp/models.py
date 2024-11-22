from django.db import models

class Товары(models.Model):
    номер_товара = models.IntegerField(primary_key=True)
    наименование = models.CharField(max_length=255)
    единица_измерения = models.CharField(max_length=255)
    цена = models.IntegerField()

    def __str__(self):
        return str(self.номер_товара)

class Чеки(models.Model):
    номер_чека = models.IntegerField(primary_key=True)
    номер_товара = models.IntegerField()
    количество = models.IntegerField()
    стоимость = models.IntegerField()

    def __str__(self):
        return str(self.номер_чека)

class Продавцы(models.Model):
    номер_чека = models.IntegerField(primary_key=True)
    дата_покупки = models.DateField()
    номер_кассы = models.IntegerField()
    продавец = models.CharField(max_length=255)

    def __str__(self):
        return str(self.номер_чека)
