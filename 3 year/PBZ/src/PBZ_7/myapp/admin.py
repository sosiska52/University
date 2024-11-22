# В файле myapp/admin.py
from django.contrib import admin
from .models import Товары, Чеки, Продавцы

@admin.register(Товары)
class ТоварыAdmin(admin.ModelAdmin):
    search_fields = ['номер_товара', 'наименование', 'единица_измерения', 'цена']
    list_display = ['номер_товара', 'наименование', 'единица_измерения', 'цена']

@admin.register(Чеки)
class ЧекиAdmin(admin.ModelAdmin):
    search_fields = ['номер_чека', 'номер_товара', 'количество', 'стоимость']
    list_display = ['номер_чека', 'номер_товара', 'количество', 'стоимость']

@admin.register(Продавцы)
class ПродавцыAdmin(admin.ModelAdmin):
    search_fields = ['номер_чека', 'дата_покупки', 'номер_кассы', 'продавец']
    list_display = ['номер_чека', 'дата_покупки', 'номер_кассы', 'продавец']
