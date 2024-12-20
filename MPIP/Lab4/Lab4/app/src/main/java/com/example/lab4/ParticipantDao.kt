package com.example.lab4

import androidx.room.*

@Dao
interface ParticipantDao {

//TODO 1: implement the functions for inserting, deleting and getting all participants

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertParticipant(participant: Participant)

    @Delete()
    suspend fun deleteParticipant(participant: Participant)

    @Query("DELETE FROM participants where id=:id")
    suspend fun deleteParticipant(id: Int)

    @Query("SELECT * FROM participants")
    suspend fun getAllParticipants(): List<Participant>

//    @Query("SELECT * FROM participants where name like :query")
//    suspend fun search
}
