package com.example.lab4

import androidx.room.Delete
import androidx.room.Query

interface LocalParticipantDataSource {

    suspend fun insertParticipant(participant: Participant)
    suspend fun deleteParticipant(participant: Participant)
    suspend fun deleteParticipant(id:Int)
    suspend fun getAllParticipants():List<Participant>
}