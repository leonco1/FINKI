package com.example.lab3.data

import android.os.Parcel
import android.os.Parcelable

data class Quote(
    val id: Int,
    val quote: String,
    val author: String
) : Parcelable {
    constructor(parcel: Parcel) : this(
        parcel.readInt(),
        parcel.readString() ?: "",
        parcel.readString() ?: ""
    )

    override fun writeToParcel(parcel: Parcel, flags: Int) {
        parcel.writeInt(id)
        parcel.writeString(quote)
        parcel.writeString(author)
    }

    override fun describeContents(): Int = 0

    companion object CREATOR : Parcelable.Creator<Quote> {
        override fun createFromParcel(parcel: Parcel): Quote {
            return Quote(parcel)
        }

        override fun newArray(size: Int): Array<Quote?> {
            return arrayOfNulls(size)
        }
    }
}
