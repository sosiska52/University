# Generated by Django 5.1.3 on 2024-11-22 10:15

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('myapp', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Билеты',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('номер_клиента', models.IntegerField()),
                ('номер_фильма', models.IntegerField()),
                ('дата', models.DateField()),
            ],
        ),
        migrations.CreateModel(
            name='Клиенты',
            fields=[
                ('номер_клиента', models.IntegerField(primary_key=True, serialize=False)),
                ('ФИО', models.CharField(max_length=255)),
                ('телефон', models.CharField(max_length=255)),
                ('адрес', models.CharField(max_length=255)),
            ],
        ),
        migrations.CreateModel(
            name='Фильмы',
            fields=[
                ('номер_фильма', models.IntegerField(primary_key=True, serialize=False)),
                ('режиссер', models.CharField(max_length=255)),
                ('название', models.CharField(max_length=255)),
                ('год_выпуска', models.DateField()),
            ],
        ),
        migrations.DeleteModel(
            name='Продавцы',
        ),
        migrations.DeleteModel(
            name='Товары',
        ),
        migrations.DeleteModel(
            name='Чеки',
        ),
    ]
