package com.example.lab4

class ParticipantRepository(private val localParticipantDataSource: LocalParticipantDataSource) {

    suspend fun insertParticipant(participant: Participant)
    {
        return localParticipantDataSource.insertParticipant(participant)
    }
    suspend fun deleteParticipant(participant: Participant)
    {
        return localParticipantDataSource.deleteParticipant(participant)
    }
    suspend fun deleteParticipantById(id:Int)
    {
        return localParticipantDataSource.deleteParticipant(id)
    }
    suspend fun listParticipants():List<Participant>
    {
        return localParticipantDataSource.getAllParticipants()
    }
}