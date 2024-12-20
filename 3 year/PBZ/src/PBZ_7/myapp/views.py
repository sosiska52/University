from django.shortcuts import render, get_object_or_404
from .models import Заведующие, Категория, Группа

def home(request):
    return render(request, 'cinema/home.html')

def заведующие_list(request):
    заведующие = Заведующие.objects.all()
    return render(request, 'cinema/заведующие_list.html', {'заведующие': заведующие})

def категории_list(request):
    категории = Категория.objects.all()
    return render(request, 'cinema/категории_list.html', {'категории': категории})

def группы_list(request):
    группы = Группа.objects.all()
    return render(request, 'cinema/группы_list.html', {'группы': группы})