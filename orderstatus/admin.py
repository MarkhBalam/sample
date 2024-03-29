

# Register your models here.
from django.contrib import admin
from .models import YourModel, Order,OrderStatus

admin.site.register(YourModel)
admin.site.register(Order)
admin.site.register(OrderStatus)
