package com.example.lab4

import android.content.Context
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider

class ParticipantsViewModelFactory(private val context: Context):ViewModelProvider.Factory {

    override fun <T : ViewModel> create(modelClass: Class<T>): T {

        return modelClass.getConstructor(ParticipantRepository::class.java).
        newInstance(ParticipantRepository(
            RoomParticipantDataSource(ParticipantDatabase.getDatabase(context).participantDao())

        ))
    }
}
