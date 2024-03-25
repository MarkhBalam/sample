from django.db import models

# Create your models here.
class Add_Product(models.Model):
    category = models.CharField(max_length=200)
    productImage = models.ImageField(upload_to="product_imgs/")
    productName = models.CharField(max_length=20)
    price = models.PositiveIntegerField()
    discount = models.DecimalField(max_digits=5, decimal_places=2)
    description =  models.CharField(max_length=200)
