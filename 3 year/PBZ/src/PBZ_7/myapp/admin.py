# В файле myapp/admin.py
from django.contrib import admin
from .models import Клиенты, Билеты, Фильмы

@admin.register(Клиенты)
class КлиентыAdmin(admin.ModelAdmin):
    search_fields = ['номер_клиента', 'ФИО', 'телефон', 'адрес']
    list_display = ['номер_клиента', 'ФИО', 'телефон', 'адрес']

@admin.register(Билеты)
class БилетыAdmin(admin.ModelAdmin):
    search_fields = ['номер_клиента', 'номер_фильма', 'дата']
    list_display = ['номер_клиента', 'номер_фильма', 'дата']

@admin.register(Фильмы)
class ФильмыAdmin(admin.ModelAdmin):
    search_fields = ['номер_фильма', 'режиссер', 'название', 'год_выпуска']
    list_display = ['номер_фильма', 'режиссер', 'название', 'год_выпуска']
