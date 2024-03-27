from django.urls import path 
from . import views 

# here are the url patterns
urlpatterns = [
    path('My_account', views.my_account,  name='My_account' ),
]
