from django.urls import path
from . import views

# here are the urls
urlpatterns = [
    path('help', views.help, name='help')
]
