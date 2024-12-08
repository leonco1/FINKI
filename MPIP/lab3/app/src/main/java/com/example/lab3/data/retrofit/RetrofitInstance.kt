package com.example.lab3.data.retrofit

import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

object RetrofitInstance {

    private const val BASE_URL = "https://dummyjson.com/"

    // This function returns the Retrofit instance
    private fun getInstance(): Retrofit {
        return Retrofit.Builder()
            .baseUrl(BASE_URL)
            .addConverterFactory(GsonConverterFactory.create())
            .build()
    }

    val apiService: RetrofitApiInterface by lazy {
        getInstance().create(RetrofitApiInterface::class.java)
    }
}
