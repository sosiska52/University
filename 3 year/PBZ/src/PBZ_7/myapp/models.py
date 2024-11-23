from django.db import models

class Клиенты(models.Model):
    номер_клиента = models.IntegerField(primary_key=True)
    ФИО = models.CharField(max_length=255)
    телефон = models.CharField(max_length=255)
    адрес = models.CharField(max_length=255)

    def __str__(self):
        return str(self.номер_клиента)

class Билеты(models.Model):
    номер_клиента = models.IntegerField()
    номер_фильма = models.IntegerField()
    дата = models.DateField()

    def __str__(self):
        return f"Клиент {self.номер_клиента}, Фильм {self.номер_фильма}"

class Фильмы(models.Model):
    номер_фильма = models.IntegerField(primary_key=True)
    режиссер = models.CharField(max_length=255)
    название = models.CharField(max_length=255)
    год_выпуска = models.DateField()

    def __str__(self):
        return self.название
