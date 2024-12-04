from django.shortcuts import render, get_object_or_404
from .models import Клиенты, Билеты, Фильмы

def home(request):
    return render(request, 'cinema/home.html')

def клиенты_list(request):
    клиенты = Клиенты.objects.all()
    return render(request, 'cinema/клиенты_list.html', {'клиенты': клиенты})

def фильмы_list(request):
    фильмы = Фильмы.objects.all()
    return render(request, 'cinema/фильмы_list.html', {'фильмы': фильмы})
